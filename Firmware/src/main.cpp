#include <Arduino.h>
#include <WiFi.h>
#include "motors.h"
#include "server.h"
#include "status.h"

const char* ssid = "SSID";
const char* password = "PASSWORD";
HomeServer server;

void setup() {
  Motors.setup();
  Status.setup();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.begin(115200);
  while(!Serial){
    delay(100);
  }
  server.setup();
  Serial.println("Ready");
  Status.setOff();
  Status.setOnGreen();
  delay(1000);
  Status.setOffGreen();
  Status.setOnBlue();
  delay(1000);
  Status.setOffBlue();
  Status.setOnRed();
  delay(1000);
  Status.setOffRed();
}

void loop() {
  Status.loop();
  server.loop();
}
