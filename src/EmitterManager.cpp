#include "EmitterManager.h"
#include "Emitter.h"
#include "FountainEmitter.h"
#include "Gravity.h"
#include "Renderer.h"
#include "Wind.h"
#include <algorithm>
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
