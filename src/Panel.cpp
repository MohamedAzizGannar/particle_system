#include "Panel.h"
#include "imgui.h"

Panel::Panel(const std::string &title, ImVec2 pos, ImVec2 size)
    : title(title), default_pos(pos), default_size(size) {}
void Panel::render() {
  if (!visible)
    return;

  ImGui::SetNextWindowPos(default_pos, ImGuiCond_FirstUseEver);
  ImGui::SetNextWindowSize(default_size, ImGuiCond_FirstUseEver);

  if (ImGui::Begin(title.c_str(), &visible))
    renderContents();
  ImGui::End();
}
