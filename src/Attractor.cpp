#include "Attractor.h"
#include "Renderer.h"
Attractor::Attractor(float strength, float2 pos, float radius)
    : Force(strength), pos(pos), radius(radius) {}
void Attractor::applyForce(Particle &p, float dt) {
  float distance_x = p.getPos().x - pos.x;
  float distance_y = p.getPos().y - pos.y;

  float2 distance_vector(distance_x, distance_y);
  float distance_sqrd = distance_vector.sqrd_length();
  if (distance_vector.length() > radius || distance_vector.length() < 4.f)
    return;
  distance_vector.normalize();
  distance_vector *= strength * 6.67e2 * p.getMass() / distance_sqrd;

  p.setVelocity(p.getVel().x - distance_vector.x * dt,
                p.getVel().y - distance_vector.y * dt);
}
void Attractor::render(Renderer &renderer) const {
  SDL_Color color = {255, 100, 255, 255}; // Magenta

  renderer.drawCircle(pos, radius, BLUE);

  SDL_Color center = {255, 255, 255, 255};
  renderer.drawCircle(pos, 1.0f, center);
}
