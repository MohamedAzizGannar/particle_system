#include "InputManager.h"
#include <SDL_events.h>

InputManager::InputManager() {};
void InputManager::update() { previousKeys = currentKeys; }
void InputManager::handleEvent(SDL_Event &event) {
  if (event.type == SDL_KEYDOWN && !event.key.repeat) {
    currentKeys[event.key.keysym.scancode] = true;
  }
  if (event.type == SDL_KEYUP)
    currentKeys[event.key.keysym.scancode] = false;
}

bool InputManager::isKeyDown(SDL_Scancode code) {
  auto it = currentKeys.find(code);
  return it != currentKeys.end() && it->second;
}
bool ::InputManager::isKeyPressed(SDL_Scancode code) {
  bool current = isKeyDown(code);

  auto it = previousKeys.find(code);
  bool previous = (it != previousKeys.end()) && it->second;

  return current && !previous;
}
