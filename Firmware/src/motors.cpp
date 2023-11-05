#include "motors.h"

void MotorsClass::setup() {
  pinMode(MOTOR_FR_DIR_B_PIN, OUTPUT);
  pinMode(MOTOR_FR_DIR_F_PIN, OUTPUT);
  pinMode(MOTOR_FR_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_FL_DIR_B_PIN, OUTPUT);
  pinMode(MOTOR_FL_DIR_F_PIN, OUTPUT);
  pinMode(MOTOR_FL_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_BR_DIR_B_PIN, OUTPUT);
  pinMode(MOTOR_BR_DIR_F_PIN, OUTPUT);
  pinMode(MOTOR_BR_SPEED_PIN, OUTPUT);
  pinMode(MOTOR_BL_DIR_B_PIN, OUTPUT);
  pinMode(MOTOR_BL_DIR_F_PIN, OUTPUT);
  pinMode(MOTOR_BL_SPEED_PIN, OUTPUT);
  setSpeeds(0,0,0,0);
}

void MotorsClass::setSpeeds(int16_t fr, int16_t fl, int16_t br, int16_t bl){
  setMotorSpeed(MOTOR_FR, fr);
  setMotorSpeed(MOTOR_FL, fl);
  setMotorSpeed(MOTOR_BR, br);
  setMotorSpeed(MOTOR_BL, bl);
}

void MotorsClass::setMotorSpeed(uint8_t motor, int16_t speed){
  uint8_t dirF = speed > 0 ? 1 : 0;
  uint8_t dirB = speed < 0 ? 1 : 0;
  uint8_t s = abs(speed);
  switch(motor){
    case MOTOR_FR:
      digitalWrite(MOTOR_FR_DIR_F_PIN, dirF);
      digitalWrite(MOTOR_FR_DIR_B_PIN, dirB);
      analogWrite(MOTOR_FR_SPEED_PIN, s);
      break;
    case MOTOR_FL:
      digitalWrite(MOTOR_FL_DIR_F_PIN, dirF);
      digitalWrite(MOTOR_FL_DIR_B_PIN, dirB);
      analogWrite(MOTOR_FL_SPEED_PIN, s);
      break;
    case MOTOR_BR:
      digitalWrite(MOTOR_BR_DIR_F_PIN, dirF);
      digitalWrite(MOTOR_BR_DIR_B_PIN, dirB);
      analogWrite(MOTOR_BR_SPEED_PIN, s);
      break;
    case MOTOR_BL:
      digitalWrite(MOTOR_BL_DIR_F_PIN, dirF);
      digitalWrite(MOTOR_BL_DIR_B_PIN, dirB);
      analogWrite(MOTOR_BL_SPEED_PIN, s);
      break;
    default:
      break;
  }
}

MotorsClass Motors;