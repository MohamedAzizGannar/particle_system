#include "EmitterManager.h"
#include "AirResistance.h"
#include "Attractor.h"
#include "Emitter.h"
#include "FountainEmitter.h"
#include "Gravity.h"
#include "Renderer.h"
#include "Repulsor.h"
#include "Wind.h"
#include <algorithm>
#include <memory>

EmitterManager::EmitterManager() {
  particles.reserve(max_particles);
  forces.reserve(max_forces);
  emitters.reserve(max_emitters);
  forces.push_back(std::make_unique<Gravity>(GRAVITY_COEFFICIENT));
  forces.push_back(std::make_unique<Wind>(WIND_COEFFICIENT, M_PI));
  forces.push_back(std::make_unique<AirResistance>(0.1));
};
void EmitterManager::update(float dt) {

  for (auto &particle : particles) {
    particle.update(dt, forces);
    particle.setAge(particle.getAge() + dt);
  }
  particles.erase(std::remove_if(particles.begin(), particles.end(),
                                 [](const Particle &p) {
                                   return p.getAge() >= p.getLifetime();
                                 }),
                  particles.end());
  for (auto &emitter : emitters) {
    emitter->emitParticles(dt);
  }
}
void EmitterManager::render(Renderer &renderer) {

  renderer.drawParticlesBatched(particles);
  if (renderForces)
    for (auto &force : forces)
      force->render(renderer);
}
void EmitterManager::addEmitter(float2 pos) {
  emitters.push_back(
      std::make_unique<Emitter>(pos, spawn_interval, particles, lifetime));
}
void EmitterManager::addFountainEmitter(float2 pos, bool isUp) {

  emitters.push_back(std::make_unique<FountainEmitter>(
      pos, spawn_interval, spread_angle, particles, lifetime, isUp));
}
void EmitterManager::toggleGravity() {
  isGravityActive = !isGravityActive;
  forces[0]->setActive(isGravityActive);
}
void EmitterManager::toggleWind() {
  isWindActive = !isWindActive;
  forces[1]->setActive(isWindActive);
}
void EmitterManager::clearEmitters() { emitters.clear(); }
void EmitterManager::addPositionalForce(float strength, float2 pos,
                                        float radius, bool isAttractor) {

  if (isAttractor)
    forces.push_back(std::make_unique<Attractor>(strength, pos, radius));
  else
    forces.push_back(std::make_unique<Repulsor>(strength, pos, radius));
}
void EmitterManager::clearForces() {

  forces.erase(forces.begin() + 3, forces.end());
}

void EmitterManager::toggleForceRendering() { renderForces = !renderForces; }
void EmitterManager::updateGravity(float new_strength) {
  forces[0]->setStrength(new_strength);
}
void EmitterManager::updateWind(float new_strength) {
  forces[1]->setStrength(new_strength);
}
void EmitterManager::updateLifetime(float lifetime_) {
  lifetime = lifetime_;
  for (auto &emitter : emitters)
    emitter->setLifetime(lifetime_);
}
void EmitterManager::updateSpawnInterval(float spawn_interval_) {
  spawn_interval = spawn_interval_;
}
void EmitterManager::updateSpreadAngle(float spread_angle_) {
  spread_angle = spread_angle_;
}
