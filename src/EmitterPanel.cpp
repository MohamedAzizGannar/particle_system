#include "EmitterPanel.h"
#include "EmitterManager.h"
#include "imgui.h"
EmitterPanel::EmitterPanel()
    : Panel("Emitter Controls", {0, 200}, {300, 400}) {}
void EmitterPanel::renderContents(EmitterManager &manager, float2 mouse_pos) {
  if (!visible)
    return;
  ImGui::SliderFloat("Particles Lifetime", &lifetime, 0.f, 10.f);
  ImGui::SliderFloat("Spawn Interval (Lower = higher Spawn Rate)",
                     &spawn_interval, 0.f, 10.f);
  ImGui::SliderFloat("Fountain Emitter Spread Angle", &spread_angle, 0.f, 10.f);

  ImGui::Spacing();

  if (ImGui::Button("Update Lifetimes")) {
    manager.updateLifetime(lifetime);
  }
  if (ImGui::Button("Update Spawn Interval")) {
    manager.updateSpawnInterval(spawn_interval);
  }
  if (ImGui::Button("Update Spread Angle")) {
    manager.updateSpreadAngle(spread_angle);
  }

  ImGui::Spacing();

  if (ImGui::Button("Clear Emitters")) {
    manager.clearEmitters();
  }
}
