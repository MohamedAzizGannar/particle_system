#include "FountainEmitter.h"
#include <cmath>

FountainEmitter::FountainEmitter(float2 pos, float spawn_interval,
                                 float spread_angle,
                                 std::vector<Particle> &particles)
    : Emitter(pos, spawn_interval, particles), spread_angle(spread_angle) {}

void FountainEmitter::generateVelocity(float2 &velocity_vector, float speed) {
  float min_angle = M_PI / 2.f - spread_angle / 2.f;
  float max_angle = M_PI / 2.f + spread_angle / 2.f;
  float angle =
      min_angle + ((float)rand() / RAND_MAX) * (max_angle - min_angle);
  velocity_vector.x = cos(angle) * speed;
  velocity_vector.y = -sin(angle) * speed;
}
