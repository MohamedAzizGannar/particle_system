#ifndef GRAVITY_H
#define GRAVITY_H
#include "Force.h"
const float GRAVITY_COEFFICIENT = 90.f;

class Gravity : public Force {

public:
  Gravity(float strength) : Force(strength) {}
  void applyForce(Particle &p, float dt) override;
};

#endif // !GRAVITY_H
