#include "../include/PhysicsSystem.h"
#include <vector>

PhysicsSystem::PhysicsSystem(std::vector<Particle> &particles, float time_step)
    : particles(particles), time_step(time_step) {}
std::vector<Particle> *PhysicsSystem::getParticles() { return &particles; }
void PhysicsSystem::update() {
  applyGravity();
  for (int i = 0; i < particles.size(); i++) {
    float nx = particles[i].getPos().x + particles[i].getVel().x * time_step;
    float ny = particles[i].getPos().y + particles[i].getVel().y * time_step;
    particles[i].setPosition(nx, ny);
  }
}
void PhysicsSystem::applyGravity() {
  for (int i = 0; i < particles.size(); i++) {
    float nx = particles[i].getVel().x + GRAVITY_COEFFICIENT * time_step;
    float ny = particles[i].getVel().y + GRAVITY_COEFFICIENT * time_step;
    particles[i].setVelocity(nx, ny);
  }
}
