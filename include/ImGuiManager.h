#ifndef IMGUIMANAGER_H
#define IMGUIMANAGER_H

#include "imgui_impl_sdl2.h"
class ImGuiManager {
private:
  bool initialized = false;

public:
  ImGuiManager(SDL_Window *window, SDL_Renderer *renderer);
  ~ImGuiManager();
  void beginFrame();
  void endFrame(SDL_Renderer *renderer);

  bool wantCaptureMouse() const;
  bool wantCaptureKeyboard() const;
};
#endif
