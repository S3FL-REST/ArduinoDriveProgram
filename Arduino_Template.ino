//Ian O'Rourke
//Arduino Setup Code

const int DELAY = 10;

String ReadSerial();
void SendSerial();

void setup() {
  Serial.begin(9600);
}

double irFrontRight = 0.0;
double irFrontLeft = 0.0;
double irBackRight = 0.0;
double irBackLeft = 0.0;

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
 
