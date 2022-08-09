#pragma once

#include <Arduino.h>
#include <Servo.h>

const uint8_t numServos = 4;

class PenguinPosition {
public:
  /*
   * @param servoPositons: Servopositionen, zu denen sich der Roboter bewegen soll (Servo-Anzahl muss immer 4 sein!)
   * @param delayAfterMovement: Wartezeit, nach dem die gewünschten Servopositionen erreicht wurden
   */
  PenguinPosition(const uint8_t *servoPositions, const uint32_t delayAfterMovement);

  /**
   * Zur im Konstruktor übergebenen Position bewegen.
   */
  void moveToPosition(Servo *servos, uint8_t *currentServoPositions) const;

private:
  void moveServoToPosition(Servo &servo, const uint8_t currentServoPosition, const uint8_t finalServoPosition) const;

  const uint8_t *m_servoPositions;
  const uint32_t m_delayAfterMovement;
};
