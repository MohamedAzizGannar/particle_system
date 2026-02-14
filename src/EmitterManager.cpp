#include "EmitterManager.h"
#include "Attractor.h"
#include "Emitter.h"
#include "FountainEmitter.h"
#include "Gravity.h"
#include "Renderer.h"
#include "Repulsor.h"
#include "Wind.h"
#include <algorithm>
#include <iostream>
#include <memory>

EmitterManager::EmitterManager() {
  forces.push_back(std::make_unique<Gravity>(GRAVITY_COEFFICIENT));
  forces.push_back(std::make_unique<Wind>(WIND_COEFFICIENT, M_PI));
};
void EmitterManager::update(float dt) {

  particles.erase(std::remove_if(particles.begin(), particles.end(),
                                 [](const Particle &p) {
                                   return p.getAge() >= p.getLifetime();
                                 }),
                  particles.end());
  std::cout << "Particle Count : " << particles.size() << std::endl;
  for (auto &emitter : emitters) {
    emitter->emitParticles(dt);
  }
  for (auto &particle : particles) {
    particle.update(dt, forces);
    particle.setAge(particle.getAge() + dt);
  }
}
void EmitterManager::render(Renderer &renderer) {
  for (auto &particle : particles) {
    particle.render(renderer);
  }
  if (renderForces)
    for (auto &force : forces)
      force->render(renderer);
}
void EmitterManager::addEmitter(float2 pos, float spawn_interval) {
  emitters.push_back(std::make_unique<Emitter>(pos, spawn_interval, particles));
}
void EmitterManager::addFountainEmitter(float2 pos, float spawn_interval,
                                        float spread_angle) {

  emitters.push_back(std::make_unique<FountainEmitter>(
      pos, spawn_interval, spread_angle, particles));
}
void EmitterManager::switchGravity() {
  isGravityActive = !isGravityActive;
  forces[0]->setActive(isGravityActive);
}
void EmitterManager::switchWind() {
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
  forces.clear();

  forces.push_back(std::make_unique<Gravity>(GRAVITY_COEFFICIENT));
  forces[0]->setActive(isGravityActive);
  forces.push_back(std::make_unique<Wind>(WIND_COEFFICIENT, M_PI));
  forces[1]->setActive(isWindActive);
}

void EmitterManager::switchForceRendering() { renderForces = !renderForces; }
