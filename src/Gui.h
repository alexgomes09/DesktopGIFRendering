//
// Created by Alex Gomes on 2025-06-11.
//

#pragma once

#include <cstdio>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class Gui {
public:
    Gui(GLFWwindow *window, const char *glsl_version);

    [[nodiscard]] int GetSidebarWidth() const;

    void Draw() const;

    ~Gui();

private:
    ImGuiWindowFlags imgui_window_flags = ImGuiWindowFlags_None;
    ImGuiStyle style;
    int sidebarWidth = 300;
};
