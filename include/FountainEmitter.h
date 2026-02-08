#ifndef FOUNTAIN_H
#define FOUNTAIN_H

#include "Emitter.h"
#include <vector>
class FoutainEmitter : public Emitter {

private:
  float min_angle;
  float max_angle;

public:
  FoutainEmitter(std::vector<Particle> &target_particles, float2 pos,
                 float spawn_rate, float min_angle = M_PI / 3.f,
                 float max_angle = 2. * M_PI / 3.);

protected:
  void generateVelocity(float &vx, float &vy, float speed) override;
};

#endif
