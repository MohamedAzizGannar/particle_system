#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <unordered_map>
class InputManager {
private:
  std::unordered_map<SDL_Scancode, bool> currentKeys;
  std::unordered_map<SDL_Scancode, bool> previousKeys;

public:
  InputManager();
  void update();
  void handleEvent(SDL_Event &event);
  bool isKeyDown(SDL_Scancode code);
  bool isKeyPressed(SDL_Scancode code);
};

#endif // !INPUTMANAGER_H
