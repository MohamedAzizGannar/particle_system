#include "Wind.h"

Wind::Wind(float strength, float direction)
    : Force(strength), direction(direction) {}
void Wind::applyForce(Particle &p, float dt) {
  float2 wind_force =
      float2(cos(direction) * strength, sin(direction) * strength);
  p.setVelocity(p.getVel().x + wind_force.x * dt,
                p.getVel().y + wind_force.y * dt);
}
