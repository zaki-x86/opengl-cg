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
    glClear(GL_COLOR_BUFFER_BIT);

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
