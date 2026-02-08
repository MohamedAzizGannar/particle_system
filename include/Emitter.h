#ifndef EMITTER_H
#define EMITTER_H

#include "Particle.h"
#include "utils.h"
#include <vector>
class Emitter {

private:
  std::vector<Particle> &target_particles;

  float2 pos;

  const int max_particle_count = 20;
  int particle_count = target_particles.size();

  float spawn_rate;
  float spawn_timer;

public:
  Emitter(std::vector<Particle> &target_particles, float2 pos,
          float spawn_rate = 0.5f);
  void emitParticles(float dt);
};

#endif // !EMITTER_H
