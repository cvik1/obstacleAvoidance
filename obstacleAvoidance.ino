/*
 * The following code use an untrasonic sensor to guide a robot
 * to avoid obstacles. 
 * This project is run on an Arduino Uno with a Adafruit motor
 * shield, two DC motors and an ultrasonic sensor.
 */
 

#include <Wire.h>
#include <Adafruit_MotorShield.h> //include motor shield library
#include "utility/Adafruit_MS_PWMServoDriver.h" 

// initialize motor shield and motor objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor1 = AFMS.getMotor(1);
Adafruit_DCMotor *myMotor2 = AFMS.getMotor(2);

// define pins for untrasonic sensor
const int trig = 12;
const int echo = 13;

void setup() {
  AFMS.begin(); // start motor shield 
  // define input/output pins for untrasonic sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT_PULLUP);
  
  myMotor1->setSpeed(100);
  myMotor2->setSpeed(100);

}

void loop() {
  long duration, distance; // ultrasonic sensor variables

  // send trigger signal 
  digitalWrite(trig, LOW); // start low to clean noise
  delayMicroseconds(2);
  digitalWrite(trig, HIGH); // high pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW); // finish low to ensure clean echo

  // read receiving signal
  duration = pulseIn(echo, HIGH); // read in off echo pin
  // convert to distance 
  distance = (duration/2) / 29; // the return time is half of total time
  // divide by 29 for speed of sounce 29cm/µs

  // check for obstacle
  if (distance < 20) { // if object is within 20cm
    myMotor1->run(FORWARD); // run motors in opposite directions to turn
    myMotor2->run(BACKWARD);
  }

  else{ // continue forward
    delay(40);
    myMotor1->run(FORWARD);
    myMotor2->run(FORWARD);
  }
}
