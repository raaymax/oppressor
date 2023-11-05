#pragma once
#include <Arduino.h>

#define MOTOR_FR 0
#define MOTOR_FL 1
#define MOTOR_BR 2
#define MOTOR_BL 4

#define MOTOR_FR_DIR_F_PIN 21
#define MOTOR_FR_DIR_B_PIN 19

#define MOTOR_FL_DIR_F_PIN 18
#define MOTOR_FL_DIR_B_PIN 5

#define MOTOR_BR_DIR_F_PIN 4
#define MOTOR_BR_DIR_B_PIN 0

#define MOTOR_BL_DIR_F_PIN 2
#define MOTOR_BL_DIR_B_PIN 15

#define MOTOR_FR_SPEED_PIN 23
#define MOTOR_FL_SPEED_PIN 22
#define MOTOR_BR_SPEED_PIN 17
#define MOTOR_BL_SPEED_PIN 16

class MotorsClass {
public:   
    void setMotorSpeed(uint8_t motor, int16_t speed);
    void setSpeeds(int16_t fr, int16_t fl, int16_t br, int16_t bl);
    void setup();
};

extern MotorsClass Motors;