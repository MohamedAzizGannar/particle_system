#include "../include/PhysicsSystem.h"
#include <vector>

PhysicsSystem::PhysicsSystem(std::vector<Particle> &particles, float time_step)
    : particles(particles), time_step(time_step) {}
std::vector<Particle> *PhysicsSystem::getParticles() { return &particles; }
void PhysicsSystem::update(float dt) {
  applyGravity(dt);
  applyDrag(dt);
  checkCollisions();
  checkLifetime();
  for (int i = 0; i < particles.size(); i++) {
    float nx = particles[i].getPos().x + particles[i].getVel().x * dt;
    float ny = particles[i].getPos().y + particles[i].getVel().y * dt;
    particles[i].setPosition(nx, ny);
    particles[i].setAge(particles[i].getAge() + dt);
  }
}
void PhysicsSystem::applyGravity(float dt) {
  for (int i = 0; i < particles.size(); i++) {
    float ny = particles[i].getVel().y + GRAVITY_COEFFICIENT * dt;
    particles[i].setVelocity(particles[i].getVel().x, ny);
  }
}
void PhysicsSystem::checkCollisions() {
  for (auto &particle : particles) {
    if (particle.getPos().x > bounding_box.pos.x + bounding_box.length) {
      particle.setVelocity(-particle.getVel().x * DAMPING_COEFFICIENT,
                           particle.getVel().y);
      particle.setPosition(bounding_box.pos.x + bounding_box.length,
                           particle.getPos().y);
    }
    if (particle.getPos().x < 0) {
      particle.setVelocity(-particle.getVel().x * DAMPING_COEFFICIENT,
                           particle.getVel().y);
      particle.setPosition(0, particle.getPos().y);
    }
    if (particle.getPos().y > bounding_box.pos.y + bounding_box.height) {
      particle.setVelocity(particle.getVel().x,
                           -particle.getVel().y * DAMPING_COEFFICIENT);
      particle.setPosition(particle.getPos().x,
                           bounding_box.pos.y + bounding_box.height);
    }
    if (particle.getPos().y < 0) {
      particle.setVelocity(particle.getVel().x,
                           -particle.getVel().y * DAMPING_COEFFICIENT);
      particle.setPosition(particle.getPos().x, 0);
    }
  }
}
void PhysicsSystem::applyDrag(float dt) {
  for (auto &particle : particles) {
    particle.setVelocity(particle.getVel().x * DRAG,
                         particle.getVel().y * DRAG);
  }
}
void PhysicsSystem::checkLifetime() {
  particles.erase(std::remove_if(particles.begin(), particles.end(),
                                 [](const Particle &p) {
                                   return p.getAge() >= p.getLifetime();
                                 }),
                  particles.end());
}
