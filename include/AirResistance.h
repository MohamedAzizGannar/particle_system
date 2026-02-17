#ifndef AIR_H
#define AIR_H
#include "Force.h"
class AirResistance : public Force {

public:
  AirResistance(float strength) : Force(strength) {}
  void applyForce(Particle &p, float dt) override;
};
#endif
