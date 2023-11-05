#include "server.h"
#include "status.h"
#include "motors.h"



HomeServer::HomeServer(): 
  server(80) {}

void HomeServer::setup() {
  Serial.print("Connecting to ");
  Serial.println(WiFi.localIP());
  Udp.begin(4000);
  server.on("/ping", HTTP_GET, std::bind(&HomeServer::handlePing, this, std::placeholders::_1));
  server.on("/speed", HTTP_POST, std::bind(&HomeServer::handleSpeeds, this, std::placeholders::_1));
  server.on("/update", HTTP_POST, std::bind(&HomeServer::handleOTA, this, std::placeholders::_1));
  server.begin();
  Status.setOnBlue();
}

void HomeServer::loop() {
  if(!update.isEmpty()){
    performOTAUpdate(update);
  }
  handleUDP();
} 

void HomeServer::handleUDP() {
  int packetSize = Udp.parsePacket();
  if (packetSize)
    {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
      handleJSONSpeeds(incomingPacket);
    }
  }
}

void HomeServer::handleJSONSpeeds(char * data) {
  DynamicJsonDocument json(255);
  deserializeJson(json, data);
  int fr = json["fr"].as<int>();
  int fl = json["fl"].as<int>();
  int br = json["br"].as<int>();
  int bl = json["bl"].as<int>();
  Motors.setSpeeds(fr, fl, br, bl);
}

void HomeServer::handleSpeeds(AsyncWebServerRequest* request) {
  if (request->hasParam("fr", true) && request->hasParam("fl", true) && request->hasParam("br", true) && request->hasParam("bl", true)) {
    int fr = request->getParam("fr", true)->value().toInt();
    int fl = request->getParam("fl", true)->value().toInt();
    int br = request->getParam("br", true)->value().toInt();
    int bl = request->getParam("bl", true)->value().toInt();
    Motors.setSpeeds(fr, fl, br, bl);
    Status.setOnGreen();
    delay(1000);
    Status.setOffGreen();
    DynamicJsonDocument jsonDoc(256);
    jsonDoc["status"] = "ok";
    sendJSON(request, 200, jsonDoc);
  } else {
    sendError(request, 400, "Missing parameters");
  }
}

void HomeServer::performOTAUpdate(String url) {
  Status.setOnRed();
  HTTPClient httpClient;
  httpClient.begin(url);

  Serial.print("Downloading OTA update from ");
  Serial.println(url);

  int httpCode = httpClient.GET();
  if (httpCode == HTTP_CODE_OK) {
    Status.setBlinkGreen();
    Update.begin(httpClient.getSize());
    Update.writeStream(httpClient.getStream());
    if (Update.end()) {
      Serial.println("OTA update successful");
    } else {
      Serial.println("OTA update failed");
    }
  } else {
    Serial.println("Unable to download OTA update");
  }
  httpClient.end();
  ESP.restart();
}

void HomeServer::sendJSON(AsyncWebServerRequest* request, const int code, DynamicJsonDocument & jsonDoc) {
  String payload;
  serializeJson(jsonDoc, payload);
  request->send(code, "application/json", payload);
}

void HomeServer::sendError(AsyncWebServerRequest* request, const int code = 500, const char * msg = "") {
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["status"] = "error";
  jsonDoc["message"] = msg;
  sendJSON(request, code, jsonDoc);
}

void HomeServer::handleOTA(AsyncWebServerRequest* request) {
  Status.setBlinkRed();
  Serial.println("update!!");
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["status"] = "dispatched";
  sendJSON(request, 200, jsonDoc);
  if (request->hasParam("url", true)) {
    update = request->getParam("url", true)->value();
    Serial.println(update);
  }
}

void HomeServer::handlePing(AsyncWebServerRequest* request) {
  DynamicJsonDocument jsonDoc(256);
  jsonDoc["status"] = "ok";
  jsonDoc["v"] = "3";
  sendJSON(request, 200, jsonDoc);
}
