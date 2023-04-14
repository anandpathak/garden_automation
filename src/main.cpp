#include <Arduino.h>

#include "config.h"
#include "wifi.h"
#include "firebase.h"   
#include "repository/remote_config.h"   
#include "helper.h"

#include <NTPClient.h>
#include <WiFiUdp.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void pumpOn(){
  Serial.print("pump up now!!");
  digitalWrite(D1,HIGH);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(5000);
  digitalWrite(D1,LOW);
  digitalWrite(LED_BUILTIN,LOW);
}

void cronScheduled(int* cronTime, freqType frequency, NTPClient currTime) {
  Serial.printf("timing: %d , freq: %d, timing: %s",cronTime[1], frequency, currTime.getFormattedTime().c_str());
  Serial.printf("frequency == DAILY, %d, timing= %d, matches= %d",frequency == DAILY, currTime.getHours() , containsInt(cronTime, currTime.getHours()));
  if (frequency == HOURLY && containsInt(cronTime, currTime.getMinutes())) {   
    pumpOn();
  } else if (frequency == DAILY && containsInt(cronTime, currTime.getHours())) {
    pumpOn();
  } else if (frequency == WEEKLY && containsInt(cronTime, currTime.getDay()) ) {
    pumpOn();
  }
  return;
}

void sendHeartBeat(int heartbeatInterval) {
  return;
}

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
  
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());


  FirebaseJson doc = getDocument();
  remoteConfig rc(doc);

  int checkIntervalInSeconds = rc.LoopWindowInSecond();
  int* cronTime = rc.TriggerTimeClockHours();
  int heartbeatInterval = rc.HeartbeatWindowInSeconds();
  freqType frequency = rc.Frequency();
  

  sendHeartBeat(heartbeatInterval);
  cronScheduled(cronTime,frequency,timeClient);
  // Serial.printf("value = %s", val);

  delay(checkIntervalInSeconds);
}