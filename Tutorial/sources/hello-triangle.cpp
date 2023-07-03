#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <stdio.h>
#include <string>
#include <fstream>
#include <filesystem>

// *** Window resize callback ***
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// *** Read a file ***
std::string readFile(const char*);

int main()
{
    // *** GLFW Initialization ***
    // ***************************
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__ // MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    if (!glfwInit())
    {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // *** GLFW Window Creation ***
    // ****************************
    GLFWwindow* window = glfwCreateWindow(800, 600, "Getting Started", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    // *** Register Callbacks ***
    // **************************
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // *** GLFW Context ***
    // ********************
    glfwMakeContextCurrent(window);

    // *** GLEW Initialization ***
    // ****************************
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    // *** Enable Depth Test ***
    // ************************
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"

    // *** Log OpenGL version and renderer ***
    // ***************************************
    const char* openglVersion = (const char*)glGetString(GL_VERSION);
    const char* rendererInfo = (const char*)glGetString(GL_RENDERER);
    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    // *****************************
    // *** ImGui Initialization ***
    // *****************************
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    ImGui::StyleColorsDark();

    // *** Make sure ImGui has context ***
    // ***********************************
    IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context.");

    // ************************
    // *** Define vertices ***
    // ************************
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    // ********************
    // Vertex Buffers
    // ********************

    // *** VAO ***
    // ***********
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // *** VBO ***
    // ***********
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ***************************************
    // Shader
    // ***************************************

    // *** Shader sources ***
    const std::string vertexShaderSrc = readFile("assets/hello-triangle/triangle.vs");
    const std::string fragmentShaderSrc = readFile("assets/hello-triangle/triangle.fs");

    // *** Compile vertex shader ***
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSrcPtr = vertexShaderSrc.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSrcPtr, NULL);
    glCompileShader(vertexShader);

    // *** Check vertex shader compile status
    // **************************************
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        printf("Failed to compile vertex shader\n");
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    // Compile fragment shader
    // ***********************
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSrcPtr = fragmentShaderSrc.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSrcPtr, NULL);
    glCompileShader(fragmentShader);

    // Check fragment shader compile status
    // ************************************
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        printf("Failed to compile fragment shader\n");
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    // Create shader program
    // *********************
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check program link status
    // *************************
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        printf("Failed to link program\n");
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("%s\n", infoLog);
    }

    // *** Delete shaders
    // ******************
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ************************************
    // Variables and Uniforms
    // ************************************
    float backgroundColor[3] = {0.2f, 0.3f, 0.3f};
    ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 0);
    ImVec4 moveTriangle = ImVec4(0.0f, 0.0f, 0.0f, 0);

    GLuint colorLoc = glGetUniformLocation(shaderProgram, "triangleColor");
    GLuint dx = glGetUniformLocation(shaderProgram, "dx");
    GLuint dy = glGetUniformLocation(shaderProgram, "dy");
    

    // ****************************
    // *** Render loop ***
    // ****************************
    while (!glfwWindowShouldClose(window))
    {
        // **************************
        // Clear Buffer
        // **************************
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 1.0f);

        // **************************
        // *** ImGui New Frame ***
        // ***********************
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // **********************
        // *** ImGui Window ***
        // **********************
        // Set window position and size
        ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Once);
        ImGui::SetNextWindowSize(ImVec2(200, 150), ImGuiCond_Once);

        ImGui::Begin("Hello Triangle");

        // *** Text ***
        ImGui::Text("OpenGL Version: %s", openglVersion);
        ImGui::Text("Renderer: %s", rendererInfo);
        ImGui::Text("Maximun number of attributes supported is %d", nrAttributes);
        ImGui::NewLine();
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "Hello!");
        ImGui::NewLine();

        // *** Triangle color Picker ***
        ImGui::Text("Change triangle color:");
        ImGui::ColorEdit3("Triangle Color", (float*)&color);

        // *** Background color Picker ***
        ImGui::Text("Change background color:");
        ImGui::ColorEdit3("Background Color", backgroundColor);

        // *** Move triangle ***
        ImGui::Text("Move triangle:");
        ImGui::SliderFloat("dx", &moveTriangle.x, -1.0f, 1.0f);
        ImGui::SliderFloat("dy", &moveTriangle.y, -1.0f, 1.0f);

        ImGui::End();

        // ***********************
        // Set Unfirom
        // ************************
        glUniform3f(colorLoc, color.x, color.y, color.z);
        glUniform1f(dx, moveTriangle.x);
        glUniform1f(dy, moveTriangle.y);

        // **********************
        // *** Draw triangle ***
        // **********************
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // ********************
        // *** ImGui Render ***
        // ********************
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // ************************************
        // *** Swap buffers and poll events ***
        // ************************************
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // **********************
    // *** Cleanup ImGui ***
    // **********************
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    // *********************************
    // optional: de-allocate all resources once they've outlived their purpose:
    // ********************************d**
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // *** GLFW Cleanup ***
    // ********************
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

std::string readFile(const char* path) {
    // read file specified by path
    std::string content;
    std::ifstream file(path);
    if(!file.is_open()) {
        printf("Failed to open file: %s\n", path);
        return "";
    }

    content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return content;
}