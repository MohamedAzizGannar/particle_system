#include "../include/PhysicsSystem.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <vector>

PhysicsSystem::PhysicsSystem(std::vector<Particle> &particles, float time_step)
    : particles(particles), time_step(time_step) {}
std::vector<Particle> *PhysicsSystem::getParticles() { return &particles; }
void PhysicsSystem::update(float dt) {
  for (auto &particle : particles) {
    particle.setAge(particle.getAge() + dt);
  }
  applyGravity(dt);
  applyDrag(dt);
  checkCollisions();
  for (int i = 0; i < particles.size(); i++) {
    float nx = particles[i].getPos().x + particles[i].getVel().x * dt;
    float ny = particles[i].getPos().y + particles[i].getVel().y * dt;
    particles[i].setPosition(nx, ny);
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
    float r = particle.getRadius();
    if (particle.getPos().x + r > bounding_box.pos.x + bounding_box.length) {
      particle.setVelocity(-particle.getVel().x * DAMPING_COEFFICIENT,
                           particle.getVel().y);
      particle.setPosition(bounding_box.pos.x + bounding_box.length - r,
                           particle.getPos().y);
    }
    if (particle.getPos().x - r < bounding_box.pos.x) {
      particle.setVelocity(-particle.getVel().x * DAMPING_COEFFICIENT,
                           particle.getVel().y);
      particle.setPosition(bounding_box.pos.x + r, particle.getPos().y);
    }
    if (particle.getPos().y + r > bounding_box.pos.y + bounding_box.height) {
      particle.setVelocity(particle.getVel().x,
                           -particle.getVel().y * DAMPING_COEFFICIENT);
      particle.setPosition(particle.getPos().x,
                           bounding_box.pos.y + bounding_box.height - r);
    }
    if (particle.getPos().y - r < bounding_box.pos.y) {
      particle.setVelocity(particle.getVel().x,
                           -particle.getVel().y * DAMPING_COEFFICIENT);
      particle.setPosition(particle.getPos().x, bounding_box.pos.x + r);
    }
  }
}
void PhysicsSystem::applyDrag(float dt) {
  for (auto &particle : particles) {
    particle.setVelocity(particle.getVel().x * DRAG,
                         particle.getVel().y * DRAG);
  }
}
BoundingBox PhysicsSystem::getBoundingBox() { return bounding_box; }
