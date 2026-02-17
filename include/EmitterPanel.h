#ifndef EMITTERPANEL_H
#define EMITTERPANEL_H
#include "EmitterManager.h"
#include "Panel.h"
class EmitterPanel : public Panel {
private:
  float spawn_interval;
  float spread_angle;
  float lifetime;

public:
  EmitterPanel();
  void renderContents(EmitterManager &manager, float2 mouse_pos);
};
#endif
