#pragma once

#include <Arduino.h>

#include "DistanceSensor.h"

class InfraredDistanceSensor : public DistanceSensor {
public:
  /**
   * @param inputPin: Analogeingang des Arduinos, an den der Sensor angeschlossen ist
   * @param minimumDistance: ADC-Wert (0-1023), ab dem isBlockedByObstacle() "true" zurückgeben soll
   */
  InfraredDistanceSensor(const uint8_t inputPin, const uint16_t minimumDistance);

  /**
   * Gibt "true" zurück, wenn der ADC-Wert den Wert von "m_minimumDistance" überschreitet.
   */
  bool isBlockedByObstacle() const;

private:
  const uint8_t m_inputPin;
  const uint16_t m_minimumDistance;
};
