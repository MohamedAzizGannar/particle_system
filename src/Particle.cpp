#include "Particle.h"

Particle::Particle(float x, float y, float vx, float vy, float mass,
                   SDL_Color color)
    : pos(x, y), vel(vx, vy), mass(mass), color(color) {}

void Particle::setPosition(float x_, float y_) {
  pos.x = x_;
  pos.y = y_;
}
void Particle::setVelocity(float x_, float y_) {
  vel.x = x_;
  vel.y = y_;
}
const float2 Particle::getPos() const { return pos; }
const float2 Particle::getVel() const { return vel; }
const SDL_Color Particle::getColor() const { return color; }
