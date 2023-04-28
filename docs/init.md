# Initializing OpenGL and GLFW

* Initializes GLFW and checks if it fails. If it fails, it prints an error message and exits the program.

```cpp
GLFWwindow* window;

/* Initialize the library */
if (!glfwInit()) {
    std::cout << "Failed to initialize GLFW" << std::endl;
    return -1;
}
```

* Create a window using GLFW. It also checks if it fails and prints an error message if it does.

```cpp
/* Create a windowed mode window and its OpenGL context */
window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
if (!window) {
    glfwTerminate();
    std::cout << "Failed to create GLFW window" << std::endl;
    return -1;
}
```

* Set window hints to OpenGL version 3.3 and use the core profile. This is required for OpenGL 3.3 and above.

```cpp
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
```

* Make the window's context current, a window context is 

```cpp
/* Make the window's context current */
glfwMakeContextCurrent(window);
```

* Initialize glew and check if it fails. If it fails, it prints an error message and exits the program.

```cpp
/* Initialize GLEW */
glewExperimental = GL_TRUE;
if (glewInit() != GLEW_OK) {
    std::cout << "Failed to initialize GLEW" << std::endl;
    return -1;
}
```

* You can log the OpenGL version and the graphics card that is being used.

```cpp
// get version info
const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
const GLubyte* version = glGetString(GL_VERSION); // version as a string
printf("Renderer: %s\n", renderer);
printf("OpenGL version supported %s\n", version);
```

* Tell GL to only draw onto a pixel if the shape is closer to the viewer

```cpp
glEnable(GL_DEPTH_TEST); // enable depth-testing
glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
```


* You may define a function that responds to window resizing. This is not required but it is recommended.

```cpp
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
```

* Set the callback function to the window.

```cpp
glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
```

* The main loop of the program. It checks if the window should close and if it should, it closes the window and exits the program.

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

* Terminate GLFW and exit the program.

```cpp
glfwTerminate();
return 0;
```

* You may add a function process keyboard input using `glfwGetKey`.

```cpp
if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
}
```

---

Now that we have everything is properly setup, you are ready to render your first triangle.

[Home](../README.md)
[Next: Rendering a triangle](triangle.md)