
#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Vector3.h>
#include <sensor_msgs/NavSatFix.h>
#include <sensor_msgs/Imu.h>

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_GPS.h>

#define UPDATE_RATE 50

ros::NodeHandle nh;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Motor Control Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#define L_ESC 5 //Teensy pin for the left motor's ESC
#define R_ESC 6 //Teensy pin for the right motor's ES

#define STOP_PWM 4915
#define RANGEPWM 1311

//Callback function for updating the left ESC
void leftESC_Change( const std_msgs::Float32& msg) {
  float scale = msg.data; //value between -1 and 1 to allow for forward & reverse
  analogWrite(L_ESC, (unsigned short)(STOP_PWM + RANGEPWM * scale));
}
//Callback function for updating the right ESC
void rightESC_Change( const std_msgs::Float32& msg) {
  float scale = msg.data; //value between -1 and 1 to allow for forward & reverse
  analogWrite(R_ESC, (unsigned short)(STOP_PWM + RANGEPWM * scale));
}

ros::Subscriber<std_msgs::Float32> Motor_leftESC("Motor_leftPWM", leftESC_Change);
ros::Subscriber<std_msgs::Float32> Motor_rightESC("Motor_rightPWM", rightESC_Change);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ IMU  Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void updateIMU(void);

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28); //Initializing the Adafruit BNO055 Sensor

geometry_msgs::Vector3 IMU_eulerOrientationMsg;
ros::Publisher IMU_eulerOrientation("IMU_eulerOrientation", &IMU_eulerOrientationMsg);

geometry_msgs::Vector3 IMU_angularVelocityMsg;
ros::Publisher IMU_angularVelocity("IMU_angularVelocity", &IMU_angularVelocityMsg);

geometry_msgs::Vector3 IMU_linearAccelerationMsg;
ros::Publisher IMU_linearAcceleration("IMU_linearAcceleration", &IMU_linearAccelerationMsg);

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GPS Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

sensor_msgs::NavSatFix navSat_msg;
ros::Publisher gpsPub("gps", &navSat_msg);

#define GPSSerial Serial2       // GPS connected to Teensy Serial port 2
Adafruit_GPS GPS(&GPSSerial);   // Connect to the GPS on the hardware port
#define GPSECHO false

// Publish Timing Control Variables
uint32_t publish_imu_time = 0;
uint32_t publish_gps_time = 0;

#define IMU_PUBLISH_RATE 10 //hz
#define GPS_PUBLISH_RATE 1 //hz

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Setup ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setup() {
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Motor Control Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //Configuring the PWM pins for output
  pinMode(L_ESC, OUTPUT);
  pinMode(R_ESC, OUTPUT);

  //Allow for 16-bits of PWM write resolution
  analogWriteResolution(16);

  //Set the frequencies for the PWM output that is sent to the ESCs
  analogWriteFrequency(L_ESC, UPDATE_RATE);
  analogWriteFrequency(R_ESC, UPDATE_RATE);

  //Set the PWM value to the ESC predetermined STOP duty cycle
  analogWrite(L_ESC, STOP_PWM);
  analogWrite(R_ESC, STOP_PWM);
  
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ IMU Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  while (!bno.begin());   //Wait until the BNO055 has been initialized

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GPS Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's
  GPS.begin(9600);
  // uncomment this line to turn on RMC
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  // uncomment this line to turn on only the "minimum" data
  //GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCONLY);
  // For parsing data, we don't suggest using anything but
  // either RMC only or RMC+GGA since
  // the parser doesn't care about other sentences at this time
  // Set the update rate
  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate

  // Request updates on antenna status, comment out to keep quiet
  GPS.sendCommand(PGCMD_ANTENNA);  
  
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ROS Configuration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //ROS initialization of the publishers and subscribers
  nh.initNode();
  nh.getHardware()->setBaud(57600);

  nh.subscribe(Motor_leftESC);
  nh.subscribe(Motor_rightESC);
  
  nh.advertise(IMU_eulerOrientation);
  nh.advertise(IMU_angularVelocity);
  nh.advertise(IMU_linearAcceleration);
  
  nh.advertise(gpsPub);
  
  while (!nh.connected()) {
    nh.spinOnce();
  }
}

void loop() {
  //Collecting the data from the BNO055
  if ((millis() - publish_imu_time) >= 1000 / IMU_PUBLISH_RATE)
  {
    updateIMU();
    publish_imu_time = millis();
  }

  // read data from the GPS in the 'main loop'
  char c = GPS.read();  
  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  //this block publishes velocity based on defined rate
  if ((millis() - publish_gps_time) >= (1000 / GPS_PUBLISH_RATE))
  {
    navSat_msg.latitude = GPS.latitude;
    navSat_msg.longitude = GPS.longitude;
    navSat_msg.altitude = GPS.altitude;
    navSat_msg.status.status = GPS.fix;
    navSat_msg.status.service = GPS.fixquality;
    gpsPub.publish(&navSat_msg);

    publish_gps_time = millis();
  }
  nh.spinOnce(); // Ensure remains connected to Ros_Serial Server
}

void updateIMU(void){
    sensors_event_t oData , aData , lData;
    bno.getEvent(&oData, Adafruit_BNO055::VECTOR_EULER);
    bno.getEvent(&aData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    bno.getEvent(&lData, Adafruit_BNO055::VECTOR_LINEARACCEL);

    //Updating the orientation publisher
    IMU_eulerOrientationMsg.x = oData.orientation.x;  // values in Euler angles or 'degrees', from 0..359
    IMU_eulerOrientationMsg.y = oData.orientation.y;  // values in Euler angles or 'degrees', from 0..359
    IMU_eulerOrientationMsg.z = oData.orientation.z;  // values in Euler angles or 'degrees', from 0..359

    //Updating the angular velocity publisher
    IMU_angularVelocityMsg.x = aData.gyro.x;  // values in rps, radians per second
    IMU_angularVelocityMsg.y = aData.gyro.y;  // values in rps, radians per second
    IMU_angularVelocityMsg.z = aData.gyro.z;  // values in rps, radians per second

    //Updating the linear acceleration publisher
    IMU_linearAccelerationMsg.x = lData.acceleration.x; // meters/second^2
    IMU_linearAccelerationMsg.y = lData.acceleration.y; // meters/second^2
    IMU_linearAccelerationMsg.z = lData.acceleration.z; // meters/second^2

    //Publishing the orientation, angular velocity, and linear acceleration Vectors
    IMU_eulerOrientation.publish(&IMU_eulerOrientationMsg);
    IMU_angularVelocity.publish(&IMU_angularVelocityMsg);
    IMU_linearAcceleration.publish(&IMU_linearAccelerationMsg);
}
