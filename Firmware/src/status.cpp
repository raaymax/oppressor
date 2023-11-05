#include "status.h"

    void StatusClass::setup(){
        lastBlink = 0;
        blinkRed = false;
        blinkGreen = false;
        blinkBlue = false;
        pinMode(STATUS_LED_RED_PIN, OUTPUT);
        pinMode(STATUS_LED_BLUE_PIN, OUTPUT);
        pinMode(STATUS_LED_GREEN_PIN, OUTPUT);
    }
    void StatusClass::loop(){
        if(millis() - lastBlink > 500){
            lastBlink = millis();
            if(blinkRed){
                digitalWrite(STATUS_LED_RED_PIN, !digitalRead(STATUS_LED_RED_PIN));
            }
            if(blinkGreen){
                digitalWrite(STATUS_LED_GREEN_PIN, !digitalRead(STATUS_LED_GREEN_PIN));
            }
            if(blinkBlue){
                digitalWrite(STATUS_LED_BLUE_PIN, !digitalRead(STATUS_LED_BLUE_PIN));
            }
        }
    }
    void StatusClass::setOnGreen(){
        digitalWrite(STATUS_LED_GREEN_PIN, HIGH);
        blinkGreen = false;
    }
    void StatusClass::setOnRed(){
        digitalWrite(STATUS_LED_RED_PIN, HIGH);
        blinkRed = false;
    }
    void StatusClass::setOnBlue(){
        digitalWrite(STATUS_LED_BLUE_PIN, HIGH);
        blinkBlue = false;
    }
    void StatusClass::setBlinkGreen(){
        digitalWrite(STATUS_LED_GREEN_PIN, HIGH);
        blinkGreen = true;
    }
    void StatusClass::setBlinkRed(){
        digitalWrite(STATUS_LED_RED_PIN, HIGH);
        blinkRed = true;
    }
    void StatusClass::setBlinkBlue(){
        digitalWrite(STATUS_LED_BLUE_PIN, HIGH);
        blinkBlue = true;
    }
    void StatusClass::setOffGreen(){
        digitalWrite(STATUS_LED_GREEN_PIN, LOW);
        blinkGreen = false;
    }
    void StatusClass::setOffRed(){
        digitalWrite(STATUS_LED_RED_PIN, LOW);
        blinkRed = false;
    }
    void StatusClass::setOffBlue(){
        digitalWrite(STATUS_LED_BLUE_PIN, LOW);
        blinkBlue = false;
    }
    void StatusClass::setOff(){
        setOffGreen();
        setOffRed();
        setOffBlue();
    }

StatusClass Status;
