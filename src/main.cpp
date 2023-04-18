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

void sendHeartBeat(std::string msg, NTPClient tc) {
  char docId[100];
  sprintf(docId, "activityLog/%d_%d_%d/%d",tc.getDay(),tc.getHours(), tc.getMinutes(),tc.getSeconds());
  FirebaseJson content;
  content.set("fields/msg/stringValue", msg);
  content.set("fields/time/stringValue", tc.getFormattedTime());
  createDocument(content, docId);
  return;
}

void pumpOn(int pumpDurationInSeconds, NTPClient timeClient){
  Serial.print("pump up on!!");
  timeClient.update();
  sendHeartBeat("pump is on", timeClient);
  digitalWrite(D1,LOW);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(pumpDurationInSeconds * 1000);
  Serial.print("pump up off!!");
  digitalWrite(D1,HIGH);
  digitalWrite(LED_BUILTIN,LOW);
  timeClient.update();
  sendHeartBeat("pump is off", timeClient);
}

void cronScheduled(int* cronTime, freqType frequency, NTPClient currTime, int pumpDurationInSeconds ) {
  Serial.printf("timing: %d , freq: %d, timing: %s",cronTime[1], frequency, currTime.getFormattedTime().c_str());
  Serial.printf("frequency == DAILY, %d, timing= %d, matches= %d",frequency == DAILY, currTime.getHours() , containsInt(cronTime, currTime.getHours()));
  if (frequency == HOURLY && containsInt(cronTime, currTime.getMinutes())) {   
    pumpOn(pumpDurationInSeconds, currTime);
  } else if (frequency == DAILY && containsInt(cronTime, currTime.getHours())) {
    pumpOn(pumpDurationInSeconds,currTime);
  } else if (frequency == WEEKLY && containsInt(cronTime, currTime.getDay()) ) {
    pumpOn(pumpDurationInSeconds, currTime);
  }
  return;
}


void setup() {
  // put your setup code here, to run once:
  
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(D1,OUTPUT);
  digitalWrite(D1,LOW);
  delay(500);
  digitalWrite(D1,HIGH);
  digitalWrite(LED_BUILTIN,LOW);

  Serial.begin(115200);
  WifiConnect();
  FireStoreConnect();  
  timeClient.begin();

}

void runCommand(int *command) {
  Serial.printf("triggering command %d %d %d", command[0], command[1], command[2]);
  if (command[0] != 1) {
    return;
  }
  uint8_t pin = (uint8_t) command[1];
  digitalWrite(pin,LOW);
  delay(command[2]*1000);
  digitalWrite(pin,HIGH);
  sendHeartBeat("triggered command", timeClient);
}


void loop() {
  
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());


  FirebaseJson doc = getDocument();
  remoteConfig rc(doc);

  int checkIntervalInSeconds = rc.LoopWindowInSecond();
  int* cronTime = rc.TriggerTimeClockHours();
  freqType frequency = rc.Frequency();
  int durationInSecond = rc.DurationInSecond();
  int *command = rc.Command();
  sendHeartBeat("loop initiated!",timeClient);
  cronScheduled(cronTime,frequency,timeClient, durationInSecond);
  if (command !=NULL) {
    runCommand(command);
  }
  delay(checkIntervalInSeconds*1000);
}