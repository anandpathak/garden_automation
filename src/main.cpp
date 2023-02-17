#include <Arduino.h>
      

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(D1,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(5000);
  digitalWrite(D1,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  
  delay(5000);
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(D1,LOW);
}