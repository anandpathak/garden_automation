#include <Arduino.h>
#if defined(ESP32)
    #include <WiFi.h>
#elif defined(ESP8266)


#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "config.h"

void WifiConnect() {
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.printf("Connecting to Wi-Fi %s, %s", WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
}

bool IsWifiConnected() {
    return WiFi.status() == WL_CONNECTED;
}