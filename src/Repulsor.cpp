
#include "Repulsor.h"
#include "Particle.h"
Repulsor::Repulsor(float strength, float2 pos, float radius)
    : Force(strength), pos(pos), radius(radius) {}
void Repulsor::applyForce(Particle &p, float dt) {

  float distance_x = p.getPos().x - pos.x;
  float distance_y = p.getPos().y - pos.y;

  float2 distance_vector(distance_x, distance_y);
  float distance_sqrd = distance_vector.sqrd_length();
  if (distance_vector.length() > radius)
    return;
  distance_vector.normalize();

  distance_vector.x *= strength * 200 / distance_sqrd;
  distance_vector.y *= strength * 200 / distance_sqrd;

  p.setVelocity(p.getVel().x + distance_vector.x * dt,
                p.getVel().y + distance_vector.y * dt);
}
void Repulsor::render(Renderer &renderer) const {
  SDL_Color color = {0, 100, 255, 255};

  renderer.drawCircle(pos, radius, GREEN);

  SDL_Color center = {255, 255, 255, 255};
  renderer.drawCircle(pos, 2.0f, center);
}
