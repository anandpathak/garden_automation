#include <iostream>

#include "remote_config.h"
#include "config_keys.h"

#define ARDUINOJSON_ENABLE_STD_STRING 1



freqType stringToFreqType(std::string ft) {
  if (ft == "HOURLY") return HOURLY;
  else if (ft == "DAILY") return DAILY; 
  else if (ft == "WEEKLY") return WEEKLY;
  else return DAILY; 
}

remoteConfig::remoteConfig(FirebaseJson j) {
  json = j;

  size_t len = json.iteratorBegin();
  FirebaseJson::IteratorValue value;
  for (size_t i = 0; i < len; i++){
    value = json.valueAt(i);
    Serial.printf("%d, Type: %s, Name: %s, Value: %s\n", i, value.type == FirebaseJson::JSON_OBJECT ? "object" : "array", value.key.c_str(), value.value.c_str());
  }
  //Clear all list to free memory
  json.iteratorEnd();        
}

int remoteConfig::LoopWindowInSecond(){
  FirebaseJsonData result;
  json.get(result, "documents/[0]/fields/"+LOOP_WINDOW_IN_SECOND_KEYS+"/integerValue");
  if (result.success) {
    return result.to<int>();
  }
  return defaultLoopWindowInSecond;
}

int remoteConfig::HeartbeatWindowInSeconds(){
  FirebaseJsonData result;
  json.get(result, "documents/[0]/fields/"+HEARTBEAT_WINDOW_IN_SECONDS_KEYS+"/integerValue");
  if (result.success) {
    return result.to<int>();
  }
  return defaultHeartbeatWindowInSeconds;
}

int remoteConfig::Version(){
  FirebaseJsonData result;
  json.get(result, "documents/[0]/fields/"+VERSION_KEYS+"/integerValue");
  if (result.success) {
    return result.to<int>();
  }
  return defaultVersion;
}

freqType remoteConfig::Frequency(){
  FirebaseJsonData result;
  json.get(result, "documents/[0]/fields/"+FREQUENCY_KEYS+"/stringValue");
  if (result.success) {
    return stringToFreqType(result.to<std::string>());
  }
  return defaultFrequency;
}

int* remoteConfig::TriggerTimeClockHours(){
  FirebaseJsonData result;
  FirebaseJsonArray arr;
  json.get(result, "documents/[0]/fields/"+TRIGGER_TIME_CLOCK_HOUR_KEYS+"/arrayValue/values");
  if (result.success) {
    result.get<FirebaseJsonArray>(arr);
    for (size_t i = 0; i < arr.size(); i++){
      FirebaseJson j;
       arr.get(result, i);
       result.get<FirebaseJson>(j);
       j.get(result,"/integerValue");
       if (result.success) {
        triggerTimeClockHour[i] = result.to<int>();
       }
    }
    return triggerTimeClockHour;
  }
  return defaultTriggerTimeClockHour;
}

int remoteConfig::DurationInSecond(){
   FirebaseJsonData result;
  json.get(result, "documents/[0]/fields/"+DURATION_IN_SECOND_KEYS+"/integerValue");
  if (result.success) {
    return result.to<int>();
  }
  return defaultDurationInSecond;
}
 


// ["ENABLED? 0,1","PORT", "DURATION"]
int* remoteConfig::Command(){
  FirebaseJsonData result;
  FirebaseJsonArray arr;
  json.get(result, "documents/[0]/fields/"+COMMAND_KEYS+"/arrayValue/values");
  if (result.success) {
    result.get<FirebaseJsonArray>(arr);
    for (size_t i = 0; i < arr.size(); i++){
      FirebaseJson j;
       arr.get(result, i);
       result.get<FirebaseJson>(j);
       j.get(result,"/integerValue");
       if (result.success) {
        commandData[i] = result.to<int>();
       }
    }
    return commandData;
  }
  return NULL;
}