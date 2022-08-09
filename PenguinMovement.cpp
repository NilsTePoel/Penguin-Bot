#include "PenguinMovement.h"

PenguinMovement::PenguinMovement(const PenguinPosition *positions, const uint8_t numSteps)
  : m_positions(positions), m_numSteps(numSteps) {
}

void PenguinMovement::executeMovement(Servo *servos, uint8_t *currentServoPositions) const {
  for (uint8_t i = 0; i < m_numSteps; i++) {
    m_positions[i].moveToPosition(servos, currentServoPositions);
  }
}
