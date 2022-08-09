#pragma once

#include <Arduino.h>

#include "PenguinServoControl.h"
#include "DistanceSensor.h"

enum class ObstacleMode {
  IGNORE,
  AVOID,
  FOLLOW
};

class PenguinObstacleDetection {
public:
  PenguinObstacleDetection(PenguinServoControl &control, const DistanceSensor &centerSensor, const DistanceSensor &leftSensor, const DistanceSensor &rightSensor);

  /**
   * Modus IGNORE: Führt keine Aktionen durch.
   * Modus AVOID: Verändert wenn erforderlich die Richtung, in die sich der Roboter bewegt, um Kollisionen mit Hindernissen
   * zu vermeiden.
   * Modus FOLLOW: Folgt einem Objekt (z. B. einer Hand), das von den Abstandssensoren erkannt wird.
   */
  void reactToObstacles();

  /**
   * Legt den Modus fest.
   * Standardmous: AVOID.
   */
  void setMode(ObstacleMode mode);

private:
  PenguinServoControl &m_control;
  const DistanceSensor &m_centerSensor;
  const DistanceSensor &m_leftSensor;
  const DistanceSensor &m_rightSensor;

  ObstacleMode m_mode;

  void avoidObstacle();
  void followObstacle();
};
