#include "Particle.h"
#include "Force.h"
#include "Renderer.h"
#include <SDL_render.h>
#include <memory>

Particle::Particle(float x, float y, float vx, float vy, SDL_Color color)
    : pos(x, y), vel(vx, vy), color(color) {}

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
  for (const auto &force : forces) {
    if (force->isActive())
      force->applyForce(*this, dt);
  }
  float2 newVel = this->getPos() + this->getVel() * dt;
  this->setPosition(newVel.x, newVel.y);
}
void Particle::render(Renderer &renderer) {
  renderer.drawCircle(pos, radius, color);
}
