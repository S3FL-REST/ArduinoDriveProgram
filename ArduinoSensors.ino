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

//Serial Communication

const int INPUT_LENGTH = 15;
char serialInput[INPUT_LENGTH];

const int NUMBER_LENGTH = 5;
char numberInput[NUMBER_LENGTH];

void setup() {
  Serial.begin(9600);
  
  talon_left_1.attach(MOTOR_L_1);
  talon_left_2.attach(MOTOR_L_2);
  talon_right_1.attach(MOTOR_R_1);
  talon_right_2.attach(MOTOR_R_2);
  
  serialInput[INPUT_LENGTH - 1] = '\0';
}

//IR Values

double irFrontRight = 0.0;
double irFrontLeft = 0.0;
double irBackRight = 0.0;
double irBackLeft = 0.0;

//Motor Values

int motorsLeft = 0;
int motorsRight = 0;
int currentLeft = 0;
int currentRight = 0;

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
  
  char *ptr = serialInput;
  *ptr = Serial.read();
  
  while (*ptr != '\r' && *ptr != '\n') {
    ++ptr;
    
    while (!Serial.available());
    
    *ptr = Serial.read();
  }
  
  ptr = serialInput;
  
  if (*ptr == 'd') {
    ++ptr; // Ignore first char
    ++ptr; // Ignore first colon
    
    //Motors Left
    
    char *numPtr = numberInput;
    
    while (*ptr != ':' && numPtr - numberInput < NUMBER_LENGTH) {
      *numPtr = *ptr;
      ++ptr; ++numPtr;
    }
    
    if (numPtr - numberInput >= NUMBER_LENGTH) goto clearserial;
    
    *numPtr = '\0';
    
    motorsLeft = atoi(numberInput);
    
    //Motors Right
    
    ++ptr;
    
    numPtr = numberInput;
    
    while (*ptr != '\n' && *ptr != '\r' && numPtr - numberInput < NUMBER_LENGTH) {
      *numPtr = *ptr;
      ++ptr; ++numPtr;
    }
    
    if (numPtr - numberInput >= NUMBER_LENGTH) goto clearserial;
    
    *numPtr = '\0';
    
    motorsRight = atoi(numberInput);
  }
  
  clearserial:
  
  while (Serial.available()) Serial.read();
  
  //motorsLeft = lValue.toInt();
  //motorsRight = rValue.toInt();
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
  if (currentLeft == motorsLeft && currentRight == motorsRight) return;
  
  int temp_l = GetPower(motorsLeft);
  int temp_r = GetPower(motorsRight);
  
  talon_left_1.write(temp_l);
  talon_left_2.write(temp_l);
  talon_right_1.write(temp_r);
  talon_right_2.write(temp_r);
  
  currentLeft = motorsLeft;
  currentRight = motorsRight;
}
 
