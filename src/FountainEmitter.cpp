#include "FountainEmitter.h"
#include <cmath>

FountainEmitter::FountainEmitter(float2 pos, float spawn_interval,
                                 float spread_angle,
                                 std::vector<Particle> &particles,
                                 float lifetime, bool up)
    : Emitter(pos, spawn_interval, particles, lifetime),
      spread_angle(spread_angle), up(up) {}

void FountainEmitter::generateVelocity(float2 &velocity_vector, float speed) {
  if (up) {

    float min_angle = M_PI / 2.f - spread_angle / 2.f;
    float max_angle = M_PI / 2.f + spread_angle / 2.f;
    float angle =
        min_angle + ((float)rand() / RAND_MAX) * (max_angle - min_angle);
    velocity_vector.x = cos(angle) * speed;
    velocity_vector.y = -sin(angle) * speed;
  } else {
    float min_angle = 3 * M_PI / 2.f - spread_angle / 2.f;
    float max_angle = 3 * M_PI / 2.f + spread_angle / 2.f;
    float angle =
        min_angle + ((float)rand() / RAND_MAX) * (max_angle - min_angle);
    velocity_vector.x = cos(angle) * speed;
    velocity_vector.y = -sin(angle) * speed;
  }
}
