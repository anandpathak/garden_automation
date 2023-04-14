#include <Arduino.h>

#include "config.h"
#include "wifi.h"
#include "firebase.h"   
#include "repository/remote_config.h"   

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
void setup() {
  // put your setup code here, to run once:
  
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(D1,OUTPUT);
  Serial.begin(115200);
  WifiConnect();
  FireStoreConnect();  
  timeClient.begin();

}

void loop() {
  
  // put your main code here, to run repeatedly:
  
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  FirebaseJson doc = getDocument();
  //const char* val = doc["documents"][0]["fields"]["Frequency"]["stringValue"];
  remoteConfig rc(doc);
  int val = rc.LoopWindowInSecond();
  int* timing = rc.TriggerTimeClockHours();
  Serial.printf("TIMING ARRAY, %d",timing[0]);

  // Serial.printf("value = %s", val);
  delay(500000);

  digitalWrite(D1,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  
  delay(5000);
  digitalWrite(LED_BUILTIN,LOW);
  digitalWrite(D1,LOW);
}

void cronScheduled(char* cronTime, NTPClient currTime) {


}