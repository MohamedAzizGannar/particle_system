#ifndef DEBUGPANEL_H
#define DEBUGPANEL_H

#include "Panel.h"
class DebugPanel : public Panel {
private:
public:
  DebugPanel();
  void renderContents(float dt, int particle_count);
};
#endif
