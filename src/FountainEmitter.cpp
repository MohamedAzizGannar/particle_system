#include "FountainEmitter.h"
#include <algorithm>
#include <cmath>

FoutainEmitter::FoutainEmitter(std::vector<Particle> &target_particles,
                               float2 pos, float spawn_rate, float min_angle,
                               float max_angle)
    : Emitter(target_particles, pos, spawn_rate), min_angle(min_angle),
      max_angle(max_angle) {}

void FoutainEmitter::generateVelocity(float &vx, float &vy, float speed) {
  float angle =
      min_angle + ((float)rand() / RAND_MAX) * (max_angle - min_angle);
  vx = cos(angle) * speed;
  vy = -sin(angle) * speed;
}
