#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H
#include "Particle.h"
#include "utils.h"
#include <vector>
const float GRAVITY_COEFFICIENT = 100.f;
const float DAMPING_COEFFICIENT = 0.9f;
const float DRAG = 0.999999f;
class PhysicsSystem {
private:
  std::vector<Particle> &particles;
  const float time_step;
  BoundingBox bounding_box = BoundingBox(float2(20., 20.), 600., 600.);

public:
  PhysicsSystem(std::vector<Particle> &particles, float time_step = 1. / 60.);
  std::vector<Particle> *getParticles();
  BoundingBox getBoundingBox();
  void applyGravity(float dt);
  void applyDrag(float dt);
  void checkCollisions();
  void update(float dt);
};

#endif // !PHYSICS_SYSTEM_H
