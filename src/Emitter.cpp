#include "Emitter.h"
#include <cmath>
#include <iostream>
#include <vector>

Emitter::Emitter(std::vector<Particle> &target_particles,
                 int current_particle_count, float spawn_rate)
    : target_particles(target_particles),
      current_particle_count(current_particle_count), spawn_rate(spawn_rate) {}

void Emitter::emitParticles(float dt) {
  spawn_timer += dt;
  if (spawn_timer >= spawn_rate) {
    if (current_particle_count < max_particle_count) {

      std::cout << "Spawn\n";
      float angle = (float(rand()) / 30) * 2.f * M_PI;
      float speed = 100.f;
      float randomVx = cos(angle) * speed;
      float randomVy = sin(angle) * speed;
      target_particles.emplace_back(250, 250, randomVx, randomVy, RED);
    }
    current_particle_count = target_particles.size();
    spawn_timer = 0.f;
  }
}
