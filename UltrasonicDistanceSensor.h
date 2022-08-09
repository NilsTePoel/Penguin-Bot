#pragma once

#include <Arduino.h>

#include "DistanceSensor.h"

class UltrasonicDistanceSensor : public DistanceSensor {
public:
  /**
   * @param triggerPin: Trigger-Eingang des Ultraschallsensors
   * @param echoPin: Echo-Ausgang des Ultraschallsensors
   * @param minimumDistance: Minimale Entfernung in cm, ab der isBlockedByObstacle() "false" zurückgeben soll
   */
  UltrasonicDistanceSensor(const uint8_t triggerPin, const uint8_t echoPin, const uint8_t minimumDistance);

  /**
   * Gibt "true" zurück, wenn die Entfernung den Wert von "m_minimumDistance" unterschreitet.
   */
  bool isBlockedByObstacle() const;

private:
  const uint8_t m_triggerPin;
  const uint8_t m_echoPin;
  const uint8_t m_minimumDistance;

  uint32_t getDistanceToObstacle() const;
};
