//Ian O'Rourke
//Arduino Setup Code

#include <Servo.h>

#include <Arduino.h>

//Variables for Motor Pins

const int MOTOR_L_1 = 3; // Left 1
const int MOTOR_L_2 = 4; // Left 2
const int MOTOR_R_1 = 5; // Right 1
const int MOTOR_R_2 = 6; // Right 2

//Delay Constant

const int DELAY = 10;

//Communication Functions

void ReadSerial();
void SendSerial();

//Motor Functions

void SetMotors();

//Talon Motors

Servo talon_left_1;
Servo talon_left_2;
Servo talon_right_1;
Servo talon_right_2;

void setup() {
  Serial.begin(9600);
  
  talon_left_1.attach(MOTOR_L_1);
  talon_left_2.attach(MOTOR_L_2);
  talon_right_1.attach(MOTOR_R_1);
  talon_right_2.attach(MOTOR_R_2);
}

//IR Values

double irFrontRight = 0.0;
double irFrontLeft = 0.0;
double irBackRight = 0.0;
double irBackLeft = 0.0;

//Motor Values

int motorsLeft = 0;
int motorsRight = 0;

//Main Run Loop

void loop() {
  ReadSerial();
  
  SetMotors();
  
  //CODE GOES HERE
  
  //SendSerial();
  delay(DELAY);
}

//Communication Code

void ReadSerial() {
  if (Serial.available() == 0) return;
  
  String serialInput = Serial.readString();
  
  Serial.println(serialInput);
  
  int colonIndex1 = serialInput.indexOf(':');
  int colonIndex2 = serialInput.indexOf(':', colonIndex1 + 1);
  
  String lValue = serialInput.substring(colonIndex1 + 1, colonIndex2);
  String rValue = serialInput.substring(colonIndex2 + 1);
  
  motorsLeft = lValue.toInt();
  motorsRight = rValue.toInt();
}

void SendSerial() {
  //IR Sensors
  
  Serial.print("i:0:");
  Serial.print(irFrontRight);
  Serial.print("\n");
  
  Serial.print("i:1:");
  Serial.print(irFrontLeft);
  Serial.print("\n");
  
  Serial.print("i:2:");
  Serial.print(irBackRight);
  Serial.print("\n");
  
  Serial.print("i:3:");
  Serial.print(irBackLeft);
  Serial.print("\n");
}

//Motor Code

int GetPower(int input) {
  if (input > 255) input = 255;
  if (input < -255) input = -255;
  
  int power = input * 90 / 255 + 90;
  
  return power;
}

void SetMotors() {
  int temp_l = GetPower(motorsLeft);
  int temp_r = GetPower(motorsRight);
  
  talon_left_1.write(temp_l);
  talon_left_2.write(temp_l);
  talon_right_1.write(temp_r);
  talon_right_2.write(temp_r);
}
 
