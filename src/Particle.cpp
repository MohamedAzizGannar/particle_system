#include "Particle.h"
#include "Force.h"
#include <SDL_render.h>
#include <memory>

Particle::Particle(float x, float y, float vx, float vy, SDL_Color color,
                   float lifetime)
    : pos(x, y), vel(vx, vy), color(color), lifetime(lifetime) {}

void Particle::setPosition(float x_, float y_) {
  pos.x = x_;
  pos.y = y_;
}
void Particle::setVelocity(float x_, float y_) {
  vel.x = x_;
  vel.y = y_;
}
void Particle::setAge(float age_) { age = age_; }

const float Particle::getVolume() const { return volume; }
const float Particle::getMass() const { return mass; }
const float2 Particle::getPos() const { return pos; }
const float2 Particle::getVel() const { return vel; }
const float Particle::getRadius() const { return radius; }

const float Particle::getAge() const { return age; }
const float Particle::getLifetime() const { return lifetime; }
const SDL_Color Particle::getColor() const { return color; }

const bool Particle::isDead() const { return age >= lifetime; }

void Particle::update(float dt,
                      const std::vector<std::unique_ptr<Force>> &forces) {
  float t = age / lifetime;
  color.r = start_color.r - t * (start_color.r - end_color.r);
  color.g = start_color.g - t * (start_color.g - end_color.g);
  color.b = start_color.b - t * (start_color.b - end_color.b);
  color.a = (Uint8)(255 * (1.0f - t));
  for (const auto &force : forces) {
    if (force->isActive())
      force->applyForce(*this, dt);
  }
  float2 newVel = this->getPos() + this->getVel() * dt;
  this->setPosition(newVel.x, newVel.y);
}
