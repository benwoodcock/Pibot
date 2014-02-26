#include <Servo.h>
const int tempsensorPin = A1;
const float baselineTemp = 32.0;
const int lightSensorPin = A0;
const int pingPin = 13;
const int motorPin1 = 9;
const int motorPin2 = 8;
Servo myservo;
int Fan = 3;
int lightSensorValue = 0;
int InfraredLed = 12;
int inPin = 11;
int safeZone = 30;

void setup(){
 Serial.begin(9600); 
 myservo.attach(7);
 myservo.write(90);
 }

void loop(){
  lightSensorValue = analogRead(lightSensorPin);
  delay(1000);
  if(lightSensorValue<780)
  { 
    digitalWrite(InfraredLed, HIGH);
  }
  else
  {
   digitalWrite(InfraredLed, LOW); 
  }
  long duration, cm;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if (cm > safeZone)
  {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH); 
  }
  else
  {
    myservo.write(0);
  }
  delay(100);
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if (cm > safeZone)
  {
   digitalWrite(motorPin1, HIGH);
   digitalWrite(motorPin2, LOW);
   delay(1000);
  }
  else
  {
   myservo.write(170);
  }
  delay(100);
    pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  if (cm > safeZone)
  {
   digitalWrite(motorPin1, LOW);
   digitalWrite(motorPin2, HIGH);
   delay(1000);
  }
  else
  {
    myservo.write(90);
  }
  
  int sensorVal = analogRead(tempsensorPin);
  Serial.print(sensorVal);
  float voltage = (sensorVal/1024.0) * 5.0;
  Serial.print(voltage);
  float temperature = (voltage - .5) * 100;
  Serial.println(temperature);
  
  if(temperature > baselineTemp)
  {
    digitalWrite(Fan, HIGH);
  }
  else
  {
    digitalWrite(Fan, LOW);
  }
  
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29 / 2;
}
