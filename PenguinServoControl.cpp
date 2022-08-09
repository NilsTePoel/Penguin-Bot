#include "PenguinServoControl.h"
#include "PenguinMovement.h"

const PenguinPosition standingPosition((const uint8_t []) {90, 90, 90, 90}, 0);

const PenguinPosition forwardMovementPositions[] = {
  PenguinPosition((const uint8_t []) {105, 125, 105, 90}, 50),
  PenguinPosition((const uint8_t []) {105, 120, 105, 115}, 50),
  PenguinPosition((const uint8_t []) {75, 110, 75, 110}, 100),
  PenguinPosition((const uint8_t []) {75, 90, 75, 55}, 250),
  PenguinPosition((const uint8_t []) {75, 60, 75, 70}, 100),
  PenguinPosition((const uint8_t []) {105, 70, 105, 70}, 100)
};
const PenguinMovement forwardMovement(forwardMovementPositions, 6);

const PenguinPosition backwardMovementPositions[] = {
  PenguinPosition((const uint8_t []) {75, 125, 75, 90}, 5),
  PenguinPosition((const uint8_t []) {75, 120, 75, 115}, 50),
  PenguinPosition((const uint8_t []) {105, 110, 105, 110}, 100),
  PenguinPosition((const uint8_t []) {105, 90, 105, 55}, 250),
  PenguinPosition((const uint8_t []) {105, 60, 105, 70}, 100),
  PenguinPosition((const uint8_t []) {75, 70, 75, 70}, 0)
};
const PenguinMovement backwardMovement(backwardMovementPositions, 6);

const PenguinPosition leftMovementPositions[] = {
  PenguinPosition((const uint8_t []) {110, 145, 110, 110}, 61),
  PenguinPosition((const uint8_t []) {70, 110, 110, 110}, 61),
  PenguinPosition((const uint8_t []) {70, 70, 110, 35}, 61),
  PenguinPosition((const uint8_t []) {70, 70, 70, 70}, 61),
  PenguinPosition((const uint8_t []) {110, 145, 70, 110}, 61),
  PenguinPosition((const uint8_t []) {70, 110, 110, 110}, 61),
  PenguinPosition((const uint8_t []) {70, 70, 110, 35}, 61),
  PenguinPosition((const uint8_t []) {70, 70, 70, 70}, 61)
};
const PenguinMovement leftMovement(leftMovementPositions, 8);

const PenguinPosition rightMovementPositions[] = {
  PenguinPosition((const uint8_t []) {110, 70, 110, 35}, 61),
  PenguinPosition((const uint8_t []) {70, 70, 110, 70}, 61),
  PenguinPosition((const uint8_t []) {70, 145, 110, 110}, 61),
  PenguinPosition((const uint8_t []) {110, 110, 70, 110}, 61),
  PenguinPosition((const uint8_t []) {110, 70, 70, 35}, 61),
  PenguinPosition((const uint8_t []) {70, 70, 110, 70}, 61),
  PenguinPosition((const uint8_t []) {70, 145, 110, 110}, 61),
  PenguinPosition((const uint8_t []) {110, 110, 70, 110}, 61)
};
const PenguinMovement rightMovement(rightMovementPositions, 8);

PenguinServoControl::PenguinServoControl(const uint8_t *servoPins)
  : m_servoPins(servoPins), m_dir(Direction::NONE), m_hasPriorityDirection(false), m_priorityDir(Direction::NONE) {
}

void PenguinServoControl::init() {
  // Servos initialisieren und auf Anfangsposition bewegen
  for (uint8_t i = 0; i < numServos; i++) {
    m_servos[i].attach(m_servoPins[i]);
    m_servos[i].write(m_currentServoPositions[i]);
  }
}

void PenguinServoControl::move() {
  Direction currentDir = m_hasPriorityDirection ? m_priorityDir : m_dir;

  switch (currentDir) {
    case Direction::NONE:
      standingPosition.moveToPosition(m_servos, m_currentServoPositions);
      break;
     case Direction::FORWARD:
      forwardMovement.executeMovement(m_servos, m_currentServoPositions);
      break;
     case Direction::BACKWARD:
      backwardMovement.executeMovement(m_servos, m_currentServoPositions);
      break;
     case Direction::LEFT:
      leftMovement.executeMovement(m_servos, m_currentServoPositions);
      break;
    case Direction::RIGHT:
      rightMovement.executeMovement(m_servos, m_currentServoPositions);
      break;
  }
}

void PenguinServoControl::setDirection(Direction dir) {
  m_dir = dir;
}

void PenguinServoControl::forceDirection(Direction dir) {
  m_hasPriorityDirection = true;
  m_priorityDir = dir;
}

void PenguinServoControl::removeForcedDirection() {
  m_hasPriorityDirection = false;
}

Direction PenguinServoControl::getDirection() const {
  return m_dir;
}
