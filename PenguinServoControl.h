#pragma once

#include <Arduino.h>
#include <Servo.h>

#include "PenguinPosition.h"

enum class Direction {
  NONE, FORWARD, BACKWARD, LEFT, RIGHT
};

class PenguinServoControl {
public:
  /** 
   *  @param servoPins: Pins, an die die vier Servos angeschlossen sind
   */
  PenguinServoControl(const uint8_t *servoPins);

  /**
   * Muss anfangs einmal aufgerufen werden.
   */
  void init();

  /**
   * Roboter bewegt sich einmal in die festgelegte Richtung.
   */
  void move();

  /**
   * Legt die Richtung fest, in der sich der Roboter bewegen soll.
   * Kann mit "forceDirection" überschrieben werden.
   */
  void setDirection(Direction dir);

  /**
   * Legt die Richtung fest, in der sich der Roboter bewegen soll.
   * Hat eine höhere Priorität als die mit "setDirection" festgelegte Richtung und
   * wird daher z. B. zum Ausweichen bei der Hinderniserkennung genutzt.
   */
  void forceDirection(Direction dir);

  /**
   * Entfernt die Richtung mit höherer Priorität.
   */
  void removeForcedDirection();

  /**
   * Gibt die Richtung zurück, die mit "setDirection" festgelegt wurde, auch wenn
   * diese überschrieben wurde.
   */
  Direction getDirection() const;

private:
  const uint8_t *m_servoPins;
  Servo m_servos[numServos];
  uint8_t m_currentServoPositions[numServos] = {90, 90, 90, 90};
  
  Direction m_dir;
  bool m_hasPriorityDirection;
  Direction m_priorityDir;
};
