#include "Emitter.h"
#include <cmath>
#include <cstdlib>
#include <vector>

Emitter::Emitter(std::vector<Particle> &target_particles, float2 pos,
                 float spawn_rate)
    : target_particles(target_particles), pos(pos), spawn_rate(spawn_rate) {}

void Emitter::emitParticles(float dt) {
  spawn_timer += dt;
  if (spawn_timer >= spawn_rate) {
    if (particle_count < max_particle_count) {
      float angle = (float(rand()) / RAND_MAX) * 2.f * M_PI;
      float speed = 100.f;
      float randomVx = cos(angle) * speed;
      float randomVy = sin(angle) * speed;
      int randomColor = rand() % 5;
      target_particles.emplace_back(pos.x, pos.y, randomVx, randomVy,
                                    colors[randomColor]);
    }
    spawn_timer = 0.f;
  }
}
