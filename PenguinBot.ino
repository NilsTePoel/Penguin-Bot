#include "PenguinBot.h"
#include "PenguinServoControl.h"
#include "UltrasonicDistanceSensor.h"
#include "InfraredDistanceSensor.h"
#include "PenguinObstacleDetection.h"

PenguinServoControl control(servoPins);

UltrasonicDistanceSensor distanceSensor(triggerPin, echoPin, minUltrasonicDistance);
InfraredDistanceSensor leftDistanceSensor(leftInfraredInputPin, minInfraredDistance);
InfraredDistanceSensor rightDistanceSensor(rightInfraredInputPin, minInfraredDistance);

PenguinObstacleDetection obstacleDetection(control, distanceSensor, leftDistanceSensor, rightDistanceSensor);

void setup() {
  control.init();

  Serial.begin(9600);
}

void loop() {
  obstacleDetection.reactToObstacles();

  control.move();
}

void serialEvent() {
  char input = Serial.read();

  switch (input) {
    case buttonForward:
      control.setDirection(Direction::FORWARD);
      break;
    case buttonBackward:
      control.setDirection(Direction::BACKWARD);
      break;
    case buttonLeft:
      control.setDirection(Direction::LEFT);
      break;
    case buttonRight:
      control.setDirection(Direction::RIGHT);
      break;
    case buttonStop:
      control.setDirection(Direction::NONE);
      break;
    case buttonManualMode:
      obstacleDetection.setMode(ObstacleMode::IGNORE);
      break;
    case buttonAvoidMode:
      obstacleDetection.setMode(ObstacleMode::AVOID);
      break;
    case buttonFollowMode:
      obstacleDetection.setMode(ObstacleMode::FOLLOW);
      break;
  }
}
