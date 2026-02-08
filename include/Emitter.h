#ifndef EMITTER_H
#define EMITTER_H

#include "Particle.h"
#include "utils.h"
#include <vector>
class Emitter {

protected:
  std::vector<Particle> &target_particles;

  float2 pos;

  const int max_particle_count = 190;
  int particle_count = 0;

  float spawn_rate;
  float spawn_timer;

public:
  Emitter(std::vector<Particle> &target_particles, float2 pos,
          float spawn_rate = 0.5f);
  void checkLifetime();
  virtual void emitParticles(float dt);
  void setPosition(float2 pos_) { pos = pos_; }
  void setSpawnRate(float rate_) { spawn_rate = rate_; }
  void decrementParticleCount() { particle_count--; }

protected:
  virtual void generateVelocity(float &vx, float &vy, float speed);
};

#endif // !EMITTER_H
