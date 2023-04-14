#ifndef REMOTE_CONFIG_H
#define REMOTE_CONFIG_H

#include <Firebase_ESP_Client.h>
#include <iostream>

enum freqType { HOURLY,DAILY, WEEKLY };

class remoteConfig {  
  FirebaseJson json;
  int defaultLoopWindowInSecond = 600;
  int defaultHeartbeatWindowInSeconds = 600;
  int defaultVersion = 1;
  freqType defaultFrequency = DAILY;
  int defaultTriggerTimeClockHour[10] = {9};
  int triggerTimeClockHour[10];
  int defaultDurationInSecond = 10;
  
public:
  remoteConfig(FirebaseJson json);
  int LoopWindowInSecond();
  int HeartbeatWindowInSeconds();
  int Version();
  freqType Frequency();
  int* TriggerTimeClockHours();
  int DurationInSecond();
};
 
#endif