#include "AirResistance.h"
#include "Particle.h"
void AirResistance::applyForce(Particle &p, float dt) {
  p.setVelocity(p.getVel().x - p.getVel().x * strength * dt,
                p.getVel().y - p.getVel().y * strength * dt);
}
