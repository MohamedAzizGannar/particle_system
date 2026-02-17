#ifndef FORCEPANEL_H
#define FORCEPANEL_H
#include "EmitterManager.h"
#include "Panel.h"
class ForcePanel : public Panel {
private:
  float attractor_strength;
  float attractor_radius;

  float repulsor_strength;
  float repulsor_radius;

  float gravity_strength;
  float wind_direction;
  float wind_strength;

public:
  ForcePanel();
  void renderContents(EmitterManager &manager);
};

#endif
