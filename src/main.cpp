#include "EmitterManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
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

int main() {

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Failure Initializating SDL : " << SDL_GetError() << std::endl;
    return -1;
  }

  bool isRunning = true;
  SDL_Event event;
  Renderer renderer(1500, 1000, "Particle System");

  InputManager inputManager;
  EmitterManager emitterManager;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard;
  ImGui::StyleColorsDark();
  ImGui_ImplSDL2_InitForSDLRenderer(renderer.getWindow(),
                                    renderer.getRenderer());
  ImGui_ImplSDLRenderer2_Init(renderer.getRenderer());

  Uint32 lastTime = SDL_GetTicks();

  float attractor_strength = 2300.f;
  float attractor_radius = 150.f;
  float repulsor_strength = 2300.f;
  float repulsor_radius = 150.f;
  float spawn_interval = 0.01f;
  float fountain_spread = M_PI / 3;

  float wind_strength = 150.f;
  float particles_lifetime = 2.f;
  while (isRunning) {

    Uint32 currentTime = SDL_GetTicks();
    float dt = (currentTime - lastTime) / 1000.f;
    lastTime = currentTime;

    inputManager.update();

    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event); // Let ImGui see events
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
      emitterManager.addEmitter(float2(mousex, mousey), spawn_interval);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_2)) {
      emitterManager.addFountainEmitter(float2(mousex, mousey), spawn_interval,
                                        fountain_spread);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_G)) {
      emitterManager.toggleGravity();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_W)) {
      emitterManager.toggleWind();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_F)) {
      emitterManager.toggleForceRendering();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_A)) {
      emitterManager.addPositionalForce(
          attractor_strength, float2(mousex, mousey), attractor_radius, true);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_R)) {
      emitterManager.addPositionalForce(
          repulsor_strength, float2(mousex, mousey), repulsor_radius, false);
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_V)) {
      emitterManager.clearForces();
    }
    if (inputManager.isKeyPressed(SDL_SCANCODE_C)) {
      emitterManager.clearEmitters();
    }
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // === YOUR UI CODE ===
    ImGui::Begin("Forces");
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Separator();
    ImGui::Text("Particle Count:%d", emitterManager.getParticleCount());
    ImGui::Separator();
    ImGui::Text("Attractor Properties");
    ImGui::SliderFloat("Attractor Strength", &attractor_strength, 0.f, 3000.f);
    ImGui::SliderFloat("Attractor Radius ", &attractor_radius, 0.f, 300.f);

    ImGui::Spacing();
    ImGui::Text("Attractor Properties");
    ImGui::SliderFloat("Repulsor Strength", &repulsor_strength, 0.f, 3000.f);
    ImGui::SliderFloat("Repulsor Radius ", &repulsor_radius, 0.f, 300.f);

    ImGui::Spacing();
    if (ImGui::Button("Toggle Gravity")) {
      emitterManager.toggleGravity();
    }
    if (ImGui::Button("Toggle Wind")) {
      emitterManager.toggleWind();
    }
    ImGui::Spacing();
    ;
    ImGui::SliderFloat("Wind Strength", &wind_strength, 0.f, 1000.f);
    if (ImGui::Button("Apply new Force")) {
      emitterManager.updateWind(wind_strength);
    }
    ImGui::End();
    ImGui::Begin("Emitters");
    ImGui::SliderFloat("Particles Lifetime", &particles_lifetime, 0.f, 10.f);
    if (ImGui::Button("Update Lifetimes")) {
      emitterManager.updateLifetime(particles_lifetime);
    }
    ImGui::End();
    emitterManager.update(dt);
    renderer.clear({0, 0, 0, 255});

    emitterManager.render(renderer);
    ImGui::Render(); // Generate ImGui draw data

    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(),
                                          renderer.getRenderer());
    renderer.present();
  }
  SDL_Quit();
  return 0;
}
