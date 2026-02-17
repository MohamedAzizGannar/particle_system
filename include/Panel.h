#ifndef PANEL_H
#define PANEL_H

#include "imgui.h"
#include "string"
class Panel {
protected:
  bool visible = true;
  std::string title;
  ImVec2 default_pos = {0, 0};
  ImVec2 default_size = {300, 400};

public:
  Panel(const std::string &title, ImVec2 pos = {0, 0},
        ImVec2 size = {300, 400});
  virtual ~Panel() = default;

  void render();
  virtual void renderContents() = 0;

  void toggle() { visible = !visible; }

  bool isVisible() { return visible; }
};

#endif
