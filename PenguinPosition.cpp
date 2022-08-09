#include "PenguinPosition.h"

PenguinPosition::PenguinPosition(const uint8_t *servoPositions, const uint32_t delayAfterMovement)
  : m_servoPositions(servoPositions), m_delayAfterMovement(delayAfterMovement) {
}

void PenguinPosition::moveToPosition(Servo *servos, uint8_t *currentServoPositions) const {
  for (uint8_t i = 0; i < numServos; i++) {
    moveServoToPosition(servos[i], currentServoPositions[i], m_servoPositions[i]); // Bewegung durchführen
    currentServoPositions[i] = m_servoPositions[i]; // Servoposition aktualisieren
  }

  // Geforderte Zeit warten
  delay(m_delayAfterMovement);
}

void PenguinPosition::moveServoToPosition(Servo &servo, const uint8_t currentServoPosition, const uint8_t finalServoPosition) const {
  uint8_t newServoPosition = currentServoPosition;

  // Hat der Servo noch nicht die Zielposition erreicht?
  while (newServoPosition != finalServoPosition) {
      const uint32_t delay = 10;
      uint32_t timeFinished = millis() + delay;

      // Servo um ein Grad bewegen
      if (newServoPosition < finalServoPosition) {
        newServoPosition++;
      } else {
        newServoPosition--;
      }
      servo.write(newServoPosition);

      // Warten, bis die Zeit abgelaufen ist
      while (millis() < timeFinished);
    }
}
