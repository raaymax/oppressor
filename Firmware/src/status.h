#pragma once
#include <Arduino.h>

#define STATUS_LED_RED_PIN 33
#define STATUS_LED_BLUE_PIN 25
#define STATUS_LED_GREEN_PIN 32

class StatusClass {
    int lastBlink;
    bool blinkRed;
    bool blinkGreen;
    bool blinkBlue;
public:
    void setup();
    void loop();
    void setOnGreen();
    void setOnRed();
    void setOnBlue();
    void setBlinkGreen();
    void setBlinkRed();
    void setBlinkBlue();
    void setOffGreen();
    void setOffRed();
    void setOffBlue();
    void setOff();
};

extern StatusClass Status;