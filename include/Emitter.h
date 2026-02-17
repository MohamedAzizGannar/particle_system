
#ifndef EMITTER_H
#define EMITTER_H
#include "Particle.h"
#include "Utility.h"
#include <vector>
class Emitter {
protected:
  float2 pos;
  float spawn_timer = 0.f;
  float spawn_interval;
  float lifetime = 2.f;
  std::vector<Particle> &particles;

public:
  Emitter(float2 pos, float spawn_interval, std::vector<Particle> &particles,
          float lifetime);

  void setLifetime(float lifetime_) { lifetime = lifetime_; }
  virtual void emitParticles(float dt);

protected:
  virtual void generateVelocity(float2 &velocity_vector, float speed);
};

#endif // !EMITTER_H
