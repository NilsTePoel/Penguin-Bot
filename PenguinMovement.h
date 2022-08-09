#pragma once

#include <Arduino.h>
#include <Servo.h>

#include "PenguinPosition.h"

class PenguinMovement {
public:
  /**
   * @param positions: Bewegungsablauf
   * @param numSteps: Anzahl an Positionen, aus denen sich der Bewegungsablauf zusammensetzts
   */
  PenguinMovement(const PenguinPosition *positions, const uint8_t numSteps);

  /**
   * Bewegungsverlauf ausführen, in dem alle im Konstruktor übergebenen Bewegungen nacheinander durchlaufen werden
   */
  void executeMovement(Servo *servos, uint8_t *currentServoPositions) const;

private:
  const PenguinPosition *m_positions;
  const uint8_t m_numSteps;
};
