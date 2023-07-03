# Getting Started

- [Getting Started](#getting-started)
  - [Initializing GLFW](#initializing-glfw)
  - [Initializing OpenGL](#initializing-opengl)
    - [OpenGL Context](#opengl-context)
    - [Getting OpenGL Functions](#getting-opengl-functions)
    - [Init OpenGL](#init-opengl)
  - [Creating GUI with Dear ImGui](#creating-gui-with-dear-imgui)
  - [Render Loop](#render-loop)
  - [Clean up](#clean-up)


We will need the following components when working with 3D graphics:

- **GLFW**: A windowing library to create a window and an OpenGL context.
- **GLEW**: A library to load OpenGL functions.
- **GLM**: A math library for 3D graphics.
- **stb_image**: A library to load images.
- **Assimp**: A library to load 3D models.
- **ImGui**: A library to create a user interface.

## Initializing GLFW

```cpp
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

```cpp
GLFWwindow* window;

/* Initialize the library */
if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
}
```

```cpp
/* Create a windowed mode window and its OpenGL context */
window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
if (!window) {
    glfwTerminate();
    std::cout << "Failed to create GLFW window" << std::endl;
    return -1;
}
```

```cpp
/* Make the window's context current */
glfwMakeContextCurrent(window);
```

- You may define a function that responds to window resizing. This is not required but it is recommended.

```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
```

- Set the callback function to the window.

```cpp
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

## Initializing OpenGL

There are two phases of OpenGL initialization:

- The first phase is the creation of an OpenGL Context.
- The second phase is to load all of the necessary functions to use OpenGL.
  
> Some non-C/C++ language bindings merge these into one.

### OpenGL Context

An opengl context is a state machine that stores all of the data related to the rendering of your application. This includes the state of the GPU, the state of the buffers, the state of the shaders, etc. The context is created by the operating system and is unique to each window. This means that if you have multiple windows, you will have multiple contexts.

We normally use a window toolkit such as: GLFW, SDL, SFML, etc. to create a window and an OpenGL context. These toolkits also provide us with a way to interact with the window and the context.

### Getting OpenGL Functions

OpenGL is a specification, not an implementation. This means that the OpenGL functions are not implemented in the OpenGL library. Instead, they are implemented in the graphics driver. This means that we need to load the functions from the graphics driver. This is done using an opengl loading library such as: GLEW, GLAD, etc.

### Init OpenGL

- Initialize glew and check if it fails. If it fails, it prints an error message and exits the program.

```cpp
/* Initialize GLEW */
glewExperimental = GL_TRUE;
if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
}
```

- You can log the OpenGL version and the graphics card that is being used.

```cpp
// get version info
const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
const GLubyte* version = glGetString(GL_VERSION); // version as a string
printf("Renderer: %s\n", renderer);
printf("OpenGL version supported %s\n", version);
```

- Tell GL to only draw onto a pixel if the shape is closer to the viewer

```cpp
glEnable(GL_DEPTH_TEST); // enable depth-testing
glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
```

## Creating GUI with Dear ImGui

- Include the necessary ImGui headers.

```cpp
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
```

- Initialize ImGui.

```cpp
/* Initialize ImGui */
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGuiIO& io = ImGui::GetIO(); (void)io;
ImGui_ImplGlfw_InitForOpenGL(window, true);
ImGui_ImplOpenGL3_Init("#version 330");
ImGui::StyleColorsDark();
```

## Render Loop

- The main loop of the program. It checks if the window should close and if it should, it closes the window and exits the program.

```cpp
/* Loop until the user closes the window */
while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}
```

- Add ImGui to the render loop.

```cpp
/* Loop until the user closes the window */
while (!glfwWindowShouldClose(window)) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* ImGui: create a new frame */
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    /* ImGui: show a simple window */
    ImGui::Begin("Hello, world!");
    ImGui::End();

    /* ImGui: render */
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    /* Swap front and back buffers */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
}
```

## Clean up

- Destroy ImGui.

```cpp
/* Cleanup ImGui */
ImGui_ImplOpenGL3_Shutdown();
ImGui_ImplGlfw_Shutdown();
ImGui::DestroyContext();
```

- Destroy the window.

```cpp
glfwDestroyWindow(window);
```

- Terminate GLFW and exit the program.

```cpp
glfwTerminate();
return 0;
```

---

Next: [Rendering a triangle](hello-triangle.md)