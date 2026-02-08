#include "Emitter.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <execution>
#include <iostream>
#include <vector>

Emitter::Emitter(std::vector<Particle> &target_particles, float2 pos,
                 float spawn_rate)
    : target_particles(target_particles), pos(pos), spawn_rate(spawn_rate) {}

void Emitter::checkLifetime() {
  for (auto &particle : target_particles) {
    if (particle.getAge() >= particle.getLifetime())
      particle_count--;
  }
  target_particles.erase(std::remove_if(target_particles.begin(),
                                        target_particles.end(),
                                        [](const Particle &p) {
                                          return p.getAge() >= p.getLifetime();
                                        }),
                         target_particles.end());
}
void Emitter::emitParticles(float dt) {
  checkLifetime();
  spawn_timer += dt;
  if (spawn_timer >= spawn_rate) {
    if (particle_count < max_particle_count) {

      float vx, vy;
      generateVelocity(vx, vy, 150.f);
      int randomColor = rand() % 5;
      target_particles.emplace_back(pos.x, pos.y, vx, vy, colors[randomColor]);
      particle_count++;
    }
    spawn_timer = 0.f;
  }
}

void Emitter::generateVelocity(float &vx, float &vy, float speed) {

  float angle = (float)((float)rand() / RAND_MAX) * 2.f * M_PI;
  vx = cos(angle) * speed;
  vy = -sin(angle) * speed;
}
