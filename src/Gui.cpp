//
// Created by Alex Gomes on 2025-06-11.
//
#include "Gui.h"

#include <iostream>
#include <ostream>

#include "../../../../../usr/local/Cellar/glfw/3.4/include/GLFW/glfw3.h"
#include "imgui/imgui_internal.h"

Gui::Gui(GLFWwindow *window, const char *glsl_version) {
    printf("%s\n", "Gui constructor");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO io = ImGui::GetIO();

    float SCALE = 1.5f;
    ImFontConfig cfg;
    cfg.SizePixels = 12 * SCALE;
    ImFont *font = io.Fonts->AddFontFromFileTTF("../assets/Roboto-Medium.ttf", cfg.SizePixels, &cfg);
    io.Fonts->Build();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsLight();

    imgui_window_flags |= ImGuiWindowFlags_AlwaysUseWindowPadding | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoMove;

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowPadding = ImVec2(5.0f, 5.0f);
    style.GrabRounding = 0.f;
    style.WindowRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.FrameRounding = 0.0f;
    style.FrameBorderSize = 1.0f;
    style.ScrollbarSize = 15.0f;
    style.AntiAliasedFill = true;
    style.AntiAliasedLines = true;
    style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
    style.WindowBorderSize = 0.0f;
    style.ScaleAllSizes(2.0f);
}

void Gui::Draw() const {
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiIO &io = ImGui::GetIO();
    ImVec2 displaySize = io.DisplaySize;

    ImGui::SetNextWindowPos(ImVec2(displaySize.x - sidebarWidth, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(sidebarWidth, displaySize.y), ImGuiCond_Always);
    ImGui::Begin("Tools", nullptr, imgui_window_flags);

    static float i1 = 0;
    ImGui::DragFloat("slider float", &i1, 1.0, 0.0, 0);
    ImGui::LogText("%f", i1);

    ImGui::End();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

int Gui::GetSidebarWidth() const {
    return sidebarWidth;
}


Gui::~Gui() {
    printf("%s\n", "Gui destructor");

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
