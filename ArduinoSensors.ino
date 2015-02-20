//Ian O'Rourke
//Arduino Setup Code

#include <Servo.h>

const int MOTOR_L_1 = 3; // Left 1
const int MOTOR_L_2 = 4; // Left 2
const int MOTOR_R_1 = 5; // Right 1
const int MOTOR_R_2 = 6; // Right 2

const int DELAY = 10;

String ReadSerial();
void SendSerial();

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

int GetPower(int input) {
  if (input > 255) input = 255;
  if (input < -255) input = -255;
  
  int power = input * 90 / 255 + 90;
  Serial.println(power);
  
  return power;
}

double irFrontRight = 0.0;
double irFrontLeft = 0.0;
double irBackRight = 0.0;
double irBackLeft = 0.0;

int motorsLeft = 0;
int motorsRight = 0;

void SetMotors(int left, int right) {
  motorsLeft = left;
  motorsRight = right;
  
  int temp_l = GetPower(left);
  int temp_r = GetPower(right);
  
  talon_left_1.write(temp_l);
  talon_left_r.write(temp_l);
  talon_right_l.write(temp_r);
  talon_right_2.write(temp_r);
}

void loop() {
  String input = ReadSerial();
  
  //CODE GOES HERE
  
  SendSerial();
  delay(DELAY);
}

String ReadSerial() {
  //CODE GOES HERE
  
  return "";
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
 
