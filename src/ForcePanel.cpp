#include "ForcePanel.h"
#include "EmitterManager.h"
#include "Panel.h"
#include "imgui.h"

ForcePanel::ForcePanel() : Panel("Force Controls", {0, 600}, {300, 400}) {}
void ForcePanel::renderContents(EmitterManager &manager) {

  ImGui::Text("Global Forces");

  ImGui::SliderFloat("Gravity Strength", &gravity_strength, 0.f, 500.f);
  ImGui::SliderFloat("Wind Strength", &wind_strength, 0.f, 500.f);
  ImGui::SliderFloat("Wind Direction", &wind_direction, 0.f, 2 * M_PI);

  if (ImGui::Button("Toggle Gravity")) {
    manager.toggleGravity();
  }
  if (ImGui::Button("Toggle Wind")) {
    manager.toggleWind();
  }

  ImGui::Separator();

  ImGui::Text("Attractor Controls");
  ImGui::SliderFloat("Attractor Strength", &attractor_strength, 0.f, 5000.f);
  ImGui::SliderFloat("Attractor Radius", &attractor_radius, 0.f, 500.f);
  ImGui::Spacing();
  ImGui::Text("Repulsor Controls");
  ImGui::SliderFloat("Repulsor Strength", &repulsor_strength, 0.f, 5000.f);
  ImGui::SliderFloat("Repulsor Radius", &repulsor_radius, 0.f, 500.f);
  if (ImGui::Button("Update All")) {
    manager.updateGravity(gravity_strength);
    manager.updateWind(wind_strength);
  }
}
