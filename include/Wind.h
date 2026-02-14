#ifndef WIND_H
#define WIND_H

#include "Particle.h"
const float WIND_COEFFICIENT = 150.f;
class Wind : public Force {
private:
  float direction;

public:
  Wind(float strength, float direction);
  void applyForce(Particle &p, float dt) override;
};

#endif // !WIND_H
