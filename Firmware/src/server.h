#pragma once
#include <WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <stdlib.h>
#include <HTTPClient.h>
#include <Update.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <WiFiUdp.h>

#define SEALEVELPRESSURE_HPA (1013.25)
#define I2C_SDA 0
#define I2C_SCL 1
#define PIXELS_PORT1 20
#define PIXELS_PORT2 21

class HomeServer {
    String update;
    AsyncWebServer server;
    WiFiUDP Udp;
    char incomingPacket[255];
public:
    HomeServer();
    void setup();
    void loop();
private:
    void handleSpeeds(AsyncWebServerRequest* request);
    void performOTAUpdate(String url);
    void handleOTA(AsyncWebServerRequest* request);
    void handlePing(AsyncWebServerRequest* request);
    void handleUDP();
    void handleJSONSpeeds(char * data);
    void sendJSON(AsyncWebServerRequest* request, const int code, DynamicJsonDocument & jsonDoc);
    void sendError(AsyncWebServerRequest* request, const int code, const char * msg);
};
