#include "Gravity.h"
#include "Particle.h"

void Gravity::applyForce(Particle &p, float dt) {
  p.setVelocity(p.getVel().x, p.getVel().y + strength * dt);
}
