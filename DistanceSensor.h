#pragma once

class DistanceSensor {
public:
  virtual bool isBlockedByObstacle() const = 0;
};
