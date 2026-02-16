#include "Emitter.h"
#include <cmath>
#include <cstdlib>

Emitter::Emitter(float2 pos, float spawn_interval,
                 std::vector<Particle> &particles)
    : pos(pos), spawn_interval(spawn_interval), particles(particles) {}

void Emitter::emitParticles(float dt) {
  spawn_timer += dt;
  if (spawn_timer >= spawn_interval) {
    float2 v;
    generateVelocity(v, 100.f);
    particles.emplace_back(pos.x, pos.y, v.x, v.y,
                           SDL_Color{255, 255, 255, 255}, lifetime);
    spawn_timer = 0.f;
  }
}
void Emitter::generateVelocity(float2 &velocity_vector, float speed) {
  float angle = ((float)rand() / RAND_MAX) * 2.f * M_PI;
  velocity_vector.x = cos(angle) * speed;
  velocity_vector.y = -sin(angle) * speed;
}
