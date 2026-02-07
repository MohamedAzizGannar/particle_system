#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "Particle.h"
#include <vector>
const float GRAVITY_COEFFICIENT = 9.8f;
class PhysicsSystem {
private:
  std::vector<Particle> &particles;
  const float time_step;

public:
  PhysicsSystem(std::vector<Particle> &particles, float time_step = 1. / 60.);
  std::vector<Particle> *getParticles();
  void applyGravity();
  void update();
};

#endif // !PHYSICS_SYSTEM_H
