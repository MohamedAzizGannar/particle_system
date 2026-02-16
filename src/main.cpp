#include "EmitterManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "imgui/imgui.h"
#include <SDL2/SDL.h>
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_mouse.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_scancode.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <iostream>
#include <ostream>

int main() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {

    std::cerr << "Failure Initializating SDL : " << SDL_GetError() << std::endl;
    return -1;
  }
  bool isRunning = true;
  SDL_Event event;
  Uint32 lastTime = SDL_GetTicks();
  Renderer renderer(800, 800, "hello");
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // ImGui::StyleColorsLight();

  // Setup scaling
  ImGuiStyle &style = ImGui::GetStyle();
  InputManager inputManager;
  EmitterManager emitterManager;
  while (isRunning) {
    Uint32 currentTime = SDL_GetTicks();
    float dt = (currentTime - lastTime) / 1000.f;
    lastTime = currentTime;
    inputManager.update();
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {

        isRunning = false;
      }
      if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
        isRunning = false;
      }
      inputManager.handleEvent(event);
    }
    int mousex;
    int mousey;
    SDL_GetMouseState(&mousex, &mousey);
    if (inputManager.isKeyPressed(SDL_SCANCODE_1)) {
      emitterManager.addEmitter(float2(mousex, mousey), 0.001f);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_2)) {
      emitterManager.addFountainEmitter(float2(mousex, mousey), 0.01f,
                                        M_PI / 3.f);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_G)) {
      emitterManager.switchGravity();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_W)) {
      emitterManager.switchWind();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_F)) {
      emitterManager.switchForceRendering();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_A)) {
      emitterManager.addPositionalForce(1300.f, float2(mousex, mousey), 150.f,
                                        true);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_R)) {
      emitterManager.addPositionalForce(1300.f, float2(mousex, mousey), 150.f,
                                        false);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_V)) {
      emitterManager.clearForces();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_C)) {
      emitterManager.clearEmitters();
    }
    emitterManager.update(dt);
    renderer.clear({0, 0, 0, 255});
    emitterManager.render(renderer);
    renderer.present();

    SDL_Delay(16);
  }
  SDL_Quit();
  std::cout << "Hello World, I'm a Particle System\n";
  return 0;
}
