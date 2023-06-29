#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>

// *** Window resize callback ***
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
    // *** GLFW Initialization ***
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__ // MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // *** GLFW Initialization ***
    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // *** GLFW Window Creation ***
    GLFWwindow* window = glfwCreateWindow(800, 600, "Getting Started", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // *** Register Callbacks ***
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // *** GLFW Context ***
    glfwMakeContextCurrent(window);

    // *** GLEW Initialization ***
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    // *** Enable Depth Test ***
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    // *** Log OpenGL version and renderer ***
    printf("OpenGL: %s\n", glGetString(GL_VERSION));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));

    // *** ImGui Initialization ***
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // *** Make sure ImGui has context ***
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context.");

    // *** Main loop ***
    while (!glfwWindowShouldClose(window))
    {
        // *** Input ***
        glfwPollEvents();

        // *** Render ***
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // *** ImGui New Frame ***
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // *** ImGui Window ***
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_Always);

        ImGui::Begin("Getting Started with OpenGL");
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Hello World!");
        ImGui::End();

        // *** ImGui Render ***
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // *** Swap buffers ***
        glfwSwapBuffers(window);
    }

    // *** Cleanup ImGui ***
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // *** GLFW Cleanup ***
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}