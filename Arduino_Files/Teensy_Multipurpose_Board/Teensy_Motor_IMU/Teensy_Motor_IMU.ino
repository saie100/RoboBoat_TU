//#define USE_TEENSY_HW_SERIAL //see rosserial_arduino for explaniation

#include <ros.h>
#include <std_msgs/Float32.h>
#include <geometry_msgs/Vector3.h>

#include <Adafruit_BNO055.h>
#include <Adafruit_Sensor.h>

#define L_ESC 5 //Teensy pin for the left motor's ESC
#define R_ESC 6 //Teensy pin for the right motor's ES

#define STOP_PWM 4915
#define RANGEPWM 1311

#define UPDATE_RATE 50

Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28); //Initializing the Adafruit BNO055 Sensor

ros::NodeHandle nh;

//Callback function for updating the left ESC
void leftESC_Change( const std_msgs::Float32& msg){
  float scale = msg.data; //value between -1 and 1 to allow for forward & reverse
  analogWrite(L_ESC, (unsigned short)(STOP_PWM + RANGEPWM*scale));
}
//Callback function for updating the right ESC
void rightESC_Change( const std_msgs::Float32& msg){
  float scale = msg.data; //value between -1 and 1 to allow for forward & reverse
  analogWrite(R_ESC, (unsigned short)(STOP_PWM + RANGEPWM*scale));
}

// Creating the subscriber variables
ros::Subscriber<std_msgs::Float32> ard_LeftESC("ard_LeftPWM", leftESC_Change);
ros::Subscriber<std_msgs::Float32> ard_RightESC("ard_RightPWM", rightESC_Change);

// Creating the publisher variables
geometry_msgs::Vector3 bno_orientationMsg;
geometry_msgs::Vector3 bno_angVelocityMsg;
geometry_msgs::Vector3 bno_linearAccelMsg;
ros::Publisher bno_orientation("bno_orientation", &bno_orientationMsg);
ros::Publisher bno_angVelocity("bno_angVelocity", &bno_angVelocityMsg);
ros::Publisher bno_linearAccel("bno_linearAccel", &bno_linearAccelMsg);


void setup() {
  //Configuring the PWM pins for output
  pinMode(L_ESC,OUTPUT);
  pinMode(R_ESC,OUTPUT);

  //Allow for 16-bits of PWM write resolution
  analogWriteResolution(16);

  //Set the frequencies for the PWM output that is sent to the ESCs
  analogWriteFrequency(L_ESC,UPDATE_RATE);
  analogWriteFrequency(R_ESC,UPDATE_RATE);

  //Set the PWM value to the ESC predetermined STOP duty cycle
  analogWrite(L_ESC, STOP_PWM);
  analogWrite(R_ESC, STOP_PWM);

  //Wait until the BNO055 has been initialized
  while(!bno.begin());

  //ROS initialization of the publishers and subscribers
  nh.initNode();
  nh.subscribe(ard_LeftESC);
  nh.subscribe(ard_RightESC);  
  nh.advertise(bno_orientation);
  nh.advertise(bno_angVelocity);
  nh.advertise(bno_linearAccel);
  
}

void loop() {
  //Collecting the data from the BNO055
  sensors_event_t orientationData , angVelocityData , linearAccelData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);

  //Updating the orientation publisher
  bno_orientationMsg.x = orientationData.orientation.x;
  bno_orientationMsg.y = orientationData.orientation.y;
  bno_orientationMsg.z = orientationData.orientation.z;

  //Updating the angular velocity publisher
  bno_angVelocityMsg.x = angVelocityData.gyro.x;
  bno_angVelocityMsg.y = angVelocityData.gyro.y;
  bno_angVelocityMsg.z = angVelocityData.gyro.z;

  //Updating the linear acceleration publisher
  bno_linearAccelMsg.x = linearAccelData.acceleration.x;
  bno_linearAccelMsg.y = linearAccelData.acceleration.y;
  bno_linearAccelMsg.z = linearAccelData.acceleration.z;

  //Publishing the orientation, angular velocity, and linear acceleration Vectors
  bno_orientation.publish(&bno_orientationMsg);
  bno_angVelocity.publish(&bno_angVelocityMsg);
  bno_linearAccel.publish(&bno_linearAccelMsg);
  nh.spinOnce(); 

  //Setting the update rate for the sensor data and ESC control
  delayMicroseconds((int)(pow(10,6)/UPDATE_RATE));
}
