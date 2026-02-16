#ifndef FORCEMANAGER_H
#define FORCEMANAGER_H
#include "Force.h"
#include "Particle.h"
#include <vector>
class ForceManager {
private:
  static const int max_force_count = 100;

  Force *forces[max_force_count];

public:
  ForceManager();
  ~ForceManager();
  void applyForces(const std::vector<Particle> &particles);
};
#endif
