#include "UltrasonicDistanceSensor.h"

UltrasonicDistanceSensor::UltrasonicDistanceSensor(const uint8_t triggerPin, const uint8_t echoPin, const uint8_t minimumDistance) 
  : m_triggerPin(triggerPin), m_echoPin(echoPin), m_minimumDistance(minimumDistance) {
  pinMode(m_triggerPin, OUTPUT);
  pinMode(m_echoPin, INPUT);
}

uint32_t UltrasonicDistanceSensor::getDistanceToObstacle() const {
  digitalWrite(m_triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(m_triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(m_triggerPin, LOW);

  uint32_t duration = pulseIn(m_echoPin, HIGH); // Dauer, bis der Schall zum Ultraschallsensor zurückkehrt (in µs)
  uint32_t distance = 0.03432 * (duration / 2); // s = v * t (in cm)

  return distance;
}

bool UltrasonicDistanceSensor::isBlockedByObstacle() const {
  return getDistanceToObstacle() < m_minimumDistance;
}
