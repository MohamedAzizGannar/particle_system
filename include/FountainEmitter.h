#ifndef FOUNTAIN_H
#define FOUNTAIN_H

#include "Emitter.h"
#include "Utility.h"
#include <vector>
class FountainEmitter : public Emitter {
private:
  float spread_angle;

public:
  FountainEmitter(float2 pos, float spawn_interval, float spread_angle,
                  std::vector<Particle> &particles);

protected:
  void generateVelocity(float2 &velocity_vector, float speed) override;
};

#endif // !FOUTAIN_H
