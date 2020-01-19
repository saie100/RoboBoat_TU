

//#define USE_TEENSY_HW_SERIAL //see rosserial_arduino for explaniation

#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Float32MultiArray.h>
/* Old PWM Pins
#define L_ESC 3
#define R_ESC 4
*/
#define L_ESC 5
#define R_ESC 6

#define STOP_PWM 4915
//#define RANGEPWM 1311 //Used for production. No limits on speed
#define RANGEPWM 600 //Used for testing. Limits speed to aprox. half. 

#define UPDATE_RATE 50

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Float32MultiArray> arduinoESC("ard_LeftPWM", leftESC_Change);


float scale;
/*
void leftESC_Change( const std_msgs::Float32& msg){
  scale = msg.data;
  analogWrite(L_ESC, (unsigned short)(STOP_PWM + RANGEPWM*scale));
  Serial.print(scale);
}

void rightESC_Change( const std_msgs::Float32& msg){
  scale = msg.data;
  analogWrite(R_ESC, (unsigned short)(STOP_PWM + RANGEPWM*scale));
  Serial.print(scale);
}

ros::Subscriber<std_msgs::Float32> leftESC("ard_LeftPWM", leftESC_Change);
ros::Subscriber<std_msgs::Float32> rightESC("ard_RightPWM", rightESC_Change);
*/




void setup() {

  pinMode(L_ESC,OUTPUT);
  pinMode(R_ESC,OUTPUT);

  analogWriteResolution(16);

  analogWriteFrequency(L_ESC,UPDATE_RATE);
  analogWriteFrequency(R_ESC,UPDATE_RATE);
  
  analogWrite(L_ESC, STOP_PWM);
  analogWrite(R_ESC, STOP_PWM);

  nh.initNode();
  nh.subscribe(arduinoESC);  

  /*
  nh.subscribe(leftESC);
  nh.subscribe(rightESC);  
  */
}

void loop() {
  // put your main code here, to run repeatedly:
  //int signal = 1500;

  //servo.writeMicroseconds(signal);

  //stepThroughFrequencies(20000);

  nh.spinOnce(); 
  delayMicroseconds((int)(pow(10,6)/UPDATE_RATE));
}
