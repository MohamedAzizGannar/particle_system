
#include "DebugPanel.h"
#include "imgui.h"
DebugPanel::DebugPanel() : Panel("Debug Panel", {0, 0}, {300, 200}) {}
void DebugPanel::renderContents(float dt, int particle_count) {
  if (!visible)
    return;
  ImGui::SetNextWindowPos(ImVec2(-1, 0), ImGuiCond_FirstUseEver);
  ImGui::Begin(title.c_str(), &visible);

  ImGui::Text("FPS : 0.1%f (%.2fms)", 1.f / dt, dt * 1000.f);
  ImGui::Text("Particle Count : %d", particle_count);

  ImGui::Separator();
}
