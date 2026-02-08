#ifndef EMITTER_H
#define EMITTER_H

#include "Particle.h"
#include "utils.h"
#include <vector>
class Emitter {

private:
  std::vector<Particle> &target_particles;
  int current_particle_count;
  const int max_particle_count = 20;
  float spawn_rate;
  float spawn_timer;

public:
  Emitter(std::vector<Particle> &target_particles, int current_particle_count,
          float spawn_rate = 0.5f);
  void emitParticles(float dt);
};

#endif // !EMITTER_H
