#include "PenguinObstacleDetection.h"

PenguinObstacleDetection::PenguinObstacleDetection(PenguinServoControl &control, const DistanceSensor &centerSensor, const DistanceSensor &leftSensor, const DistanceSensor &rightSensor)
  : m_control(control), m_centerSensor(centerSensor), m_leftSensor(leftSensor), m_rightSensor(rightSensor), m_mode(ObstacleMode::AVOID) {
}

void PenguinObstacleDetection::reactToObstacles() {
  switch (m_mode) {
    case ObstacleMode::IGNORE:
    {
      // Hinderniserkennung nicht aktiv -> normal weiterbewegen
      m_control.removeForcedDirection();
      break;
    }
    case ObstacleMode::AVOID:
    {
      if (m_control.getDirection() == Direction::FORWARD) {
        // Der Roboter weicht nur Hindernissen aus, wenn er sich nach vorne bewegt,
        // da er nur vorne Abstandssensoren hat
        avoidObstacle();
      } else {
        // Ausweichen nicht möglich -> normal weiterbewegen
        m_control.removeForcedDirection();
      }
      break;
    }
    case ObstacleMode::FOLLOW:
    {
      // Im Folgemodus bewegt sich der Roboter unabhängig von der vom Nutzer eingestellten Richtung
      followObstacle();
      break;
    }
  }
}

void PenguinObstacleDetection::avoidObstacle() {
  if (m_leftSensor.isBlockedByObstacle() && !m_rightSensor.isBlockedByObstacle()) {
    // Nur links wird ein Hindernis erkannt -> nach rechts drehen
    m_control.forceDirection(Direction::RIGHT);
  } else if (!m_leftSensor.isBlockedByObstacle() && m_rightSensor.isBlockedByObstacle()) {
    // Nur rechts wird ein Hindernis erkannt -> nach links drehen
    m_control.forceDirection(Direction::LEFT);
  } else if ((m_leftSensor.isBlockedByObstacle() && m_rightSensor.isBlockedByObstacle()) || m_centerSensor.isBlockedByObstacle()) {
    // Auf beiden Seiten wird ein Hindernis erkannt oder das Hindernis befindet sich unmittelbar vor dem
    // Roboter (d. h. "centerSensor" ist durch ein Hindernis blockiert) -> zurück bewegen
    m_control.forceDirection(Direction::BACKWARD);
  } else {
    // Kein Hindernis erkannt -> normal weiterbewegen
    m_control.removeForcedDirection();
  }
}

void PenguinObstacleDetection::followObstacle() {
  if (m_leftSensor.isBlockedByObstacle() && !m_rightSensor.isBlockedByObstacle()) {
    // Nur links wird ein Hindernis erkannt -> nach links drehen
    m_control.forceDirection(Direction::LEFT);
  } else if (!m_leftSensor.isBlockedByObstacle() && m_rightSensor.isBlockedByObstacle()) {
    // Nur rechts wird ein Hindernis erkannt -> nach rechts drehen
    m_control.forceDirection(Direction::RIGHT);
  } else if ((m_leftSensor.isBlockedByObstacle() && m_rightSensor.isBlockedByObstacle()) || m_centerSensor.isBlockedByObstacle()){
    // Auf beiden Seiten wird ein Hindernis erkannt oder der das Hindernis befindet sich unmittelbar vor dem
    // Roboter (d. h. "centerSensor" ist durch ein Hindernis blockiert) -> nach vorne bewegen
    m_control.forceDirection(Direction::FORWARD);
  } else {
    // Kein Hindernis erkannt -> stehen bleiben
    m_control.forceDirection(Direction::NONE);
  }
}

void PenguinObstacleDetection::setMode(ObstacleMode mode) {
  m_mode = mode;
}
