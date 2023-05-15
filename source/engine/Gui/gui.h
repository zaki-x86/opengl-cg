#pragma once

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../core/Window.h"

#include <functional>

enum class GraphicsFramework
{
    VULKAN,
    OPENGL
};

enum class WindowHandler
{
    GLFW,
    SDL
};

static GraphicsFramework fm = GraphicsFramework::OPENGL;

class EngineGui
{
public:
    EngineGui(GLFWwindow *window) : m_window(window), m_windowFlags(0) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        m_io = &ImGui::GetIO();

        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // Setup Platform/Renderer bindings
        if (fm == GraphicsFramework::OPENGL) {
            ImGui_ImplGlfw_InitForOpenGL(m_window, true);
            ImGui_ImplOpenGL3_Init("#version 330 core");
        }

        // Our state
        //bool show_demo_window = true;
        //bool show_another_window = false;
        //ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    }
    
    ~EngineGui() {
        if (fm == GraphicsFramework::OPENGL) {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
        }
    }

    ImGuiIO& GetIO() {
        return *m_io;
    }

    inline void render() {
        if (fm == GraphicsFramework::OPENGL) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }
    }

    inline void renderEnd() {
        if (fm == GraphicsFramework::OPENGL) {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
    }

    inline bool beginMainUI(bool* p_open) {
        // Check if context exists
        IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context.");

        ImGuiWindowFlags window_flags = 0;

        // Main body of the Demo window starts here.
        if (!ImGui::Begin("Engine Interface", p_open, window_flags))
        {
            // Early out if the window is collapsed, as an optimization.
            ImGui::End();
            return false;
        }

        ImGui::Text("This engine uses ImGui Version: (%s) (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);
        ImGui::Spacing();

        return true;
    }

    inline void endMainUI() {
        ImGui::End();
    }

private:
    GLFWwindow *m_window;
    ImGuiIO* m_io;
    ImGuiWindowFlags m_windowFlags;
};