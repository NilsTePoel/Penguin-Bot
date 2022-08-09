#include "InfraredDistanceSensor.h"

InfraredDistanceSensor::InfraredDistanceSensor(const uint8_t inputPin, const uint16_t minimumDistance) 
  : m_inputPin(inputPin), m_minimumDistance(minimumDistance) {
}

bool InfraredDistanceSensor::isBlockedByObstacle() const {
  uint16_t inputValue = analogRead(m_inputPin);

  // ADC-Wert nimmt mit geringer werdender Entfernung zu
  return inputValue > m_minimumDistance;
}
