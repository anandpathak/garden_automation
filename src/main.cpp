#include <Arduino.h>

#include "config.h"
#include "wifi.h"
#include "firebase.h"      
void setup() {
  // put your setup code here, to run once:
  
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(D1,OUTPUT);
  Serial.begin(115200);
  WifiConnect();
  FireStoreConnect();

}

void loop() {
  
  // put your main code here, to run repeatedly:
  DynamicJsonDocument doc = getDocument();
  const char* val = doc["documents"][0]["fields"]["Frequency"]["stringValue"];
  Serial.printf("value = %s", val);
  delay(500000);

  digitalWrite(D1,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  
  delay(5000);
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(D1,LOW);
}