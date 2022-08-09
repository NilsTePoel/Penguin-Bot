#include "PenguinServoControl.h"

const uint8_t servoLeftLegPin = 10;
const uint8_t servoLeftFootPin = 12;
const uint8_t servoRightLegPin = 9;
const uint8_t servoRightFootPin = 6;
const uint8_t servoPins[numServos] = {servoLeftLegPin, servoLeftFootPin, servoRightLegPin, servoRightFootPin};

const uint8_t triggerPin = 5;
const uint8_t echoPin = 4;
const uint8_t minUltrasonicDistance = 5;

const uint8_t leftInfraredInputPin = A0;
const uint8_t rightInfraredInputPin = A1;
const uint16_t minInfraredDistance = 400; // ADC-Wert, experimentell bestimmt

const char buttonForward = 'f';
const char buttonBackward = 'b';
const char buttonLeft = 'l';
const char buttonRight = 'r';
const char buttonStop = 's';
const char buttonManualMode = 'm';
const char buttonAvoidMode = 'a';
const char buttonFollowMode = 'o';
