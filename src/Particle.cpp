#include "Particle.h"
#include "Force.h"
#include "Renderer.h"
#include <SDL_render.h>
#include <algorithm>
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

const float2 Particle::getPos() const { return pos; }
const float2 Particle::getVel() const { return vel; }
const float Particle::getRadius() const { return radius; }
const SDL_Color Particle::getColor() const { return color; }

const float Particle::getAge() const { return age; }
const float Particle::getLifetime() const { return lifetime; }

const bool Particle::isDead() const { return age >= lifetime; }

void Particle::update(float dt,
                      const std::vector<std::unique_ptr<Force>> &forces) {
  for (const auto &force : forces) {
    if (force->isActive())
      force->applyForce(*this, dt);
  }

  this->setPosition(this->getPos().x + this->getVel().x * dt,
                    this->getPos().y + this->getVel().y * dt);
}
void Particle::render(Renderer &renderer) {
  renderer.drawCircle(pos, radius, color);
}
