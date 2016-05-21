// this constant won't change.  It's the pin number
// of the sensor's output:
#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial seri1 (11, 12); // RX, TX
Servo myservo;
const int pingPin = 7;
int jalan = 1;
int berhenti = 0;
int incomingByte = 0;

void setup() {
  pinMode(3, OUTPUT);
  // initialize serial communication:
  Serial.begin(115200);
  seri1.begin(115200);
  myservo.attach(10);
  myservo.write(90);
}

void loop() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);

  if(cm > 100){
    Serial.print(jalan);
  } else {
    Serial.print(berhenti);
  }
  
  incomingByte = seri1.read();
  if(incomingByte == 1){
  kanan();
  } else if(incomingByte == 2){
  kiri();
  }
  
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void kanan(){
  int ulang = 90;
  digitalWrite(3, HIGH);
  for(ulang = 90; ulang <= 120; ulang += 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(ulang);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  }
Serial.print(jalan);
delay(1000);
Serial.print(berhenti);
myservo.write(90);   
}

void kiri(){
  int ulang = 90;
  digitalWrite(3, LOW);
  for(ulang = 90; ulang >= 60; ulang -= 1) // goes from 0 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(ulang);              // tell servo to go to position in variable 'pos' 
    delay(15);                       // waits 15ms for the servo to reach the position 
  } 
Serial.print(jalan);
delay(1000);
Serial.print(berhenti);
myservo.write(90);  
}


