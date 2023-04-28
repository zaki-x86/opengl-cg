# Hello Triangle

## Define the vertex data of the triangle

For now let's draw a flat triangle onto the final screen area; x between -1 and 1, y between -1 and 1, and z = 0.

Our vertices must be in normalized device coordinates (NDC) in order to be drawn on the screen. NDC is a coordinate system that is relative to the screen. The origin is at the center of the screen, the x-axis goes from -1 to 1 from left to right, and the y-axis goes from -1 to 1 from bottom to top. The z-axis goes from -1 to 1 from the front to the back of the screen. Any coordinates that fall outside this range will be discarded/clipped and won't be visible on your screen.

```cpp
float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f,  0.5f, 0.0f
};
```

## Create a vertex buffer object (VBO)

In this step, we are going to create memory on the GPU where we store the vertex data. We do this by generating a unique ID for the buffer and then binding it to the `GL_ARRAY_BUFFER` target. After that, we copy the vertex data into the buffer by calling `glBufferData`.

```cpp
unsigned int VBO;
glGenBuffers(1, &VBO);
glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
```

* `glGenBuffers(1, &VBO)`: generates a buffer object ID and stores it in the unsigned int variable `VBO`. `1` specifies the number of buffer objects to generate.
* `glBindBuffer(GL_ARRAY_BUFFER, VBO)`: binds the buffer object with ID `VBO` to the `GL_ARRAY_BUFFER` target. This means that all subsequent `GL_ARRAY_BUFFER` operations will affect the buffer object `VBO`.
* `glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW)`: copies the previously defined vertex data into the buffer's memory. `GL_STATIC_DRAW` tells OpenGL that the data will most likely not change at all or very rarely. This allows OpenGL to optimize the buffer in certain ways.

## Create a vertex array object (VAO)

A VAO stores the vertex attribute configuration and which VBO to use. We do this by generating a unique ID for the VAO and then binding it to the `GL_VERTEX_ARRAY` target. After that, we configure the vertex attribute pointers by calling `glVertexAttribPointer` and enable the vertex attributes by calling `glEnableVertexAttribArray`.

```cpp
unsigned int VAO;
glGenVertexArrays(1, &VAO);
glBindVertexArray(VAO);
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

* `glGenVertexArrays(1, &VAO)`: generates a vertex array object ID and stores it in the unsigned int variable `VAO`. `1` specifies the number of vertex array objects to generate.
* `glBindVertexArray(VAO)`: binds the vertex array object. All subsequent vertex attribute configurations will be stored in the VAO.
* `glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0)`: configures the vertex attribute pointers.
  * The first argument specifies which vertex attribute we want to configure. Remember that we specified the location of the vertex position in the vertex shader with `layout (location = 0)`.
  * The next argument specifies the size of the vertex attribute. The vertex attribute is a `vec3` so it is composed of 3 values.
  * The third argument specifies the type of the data. The vertex attribute is a `vec3` so it is composed of floats.
  * The fourth argument specifies if we want the data to be normalized. The vertex attribute is a `vec3` so it is composed of floats between -1 and 1.
  * The fifth argument specifies the stride between consecutive vertex attributes. Since the next vertex position is located exactly 3 times the size of a float away we specify `3 * sizeof(float)`.
  * The last argument specifies the offset of where the position data begins in the buffer. Since the position data is at the start of the buffer we specify `(void*)0`.
* `glEnableVertexAttribArray(0)`: enables the vertex attribute at location 0. Since we specified the location of the vertex position with `layout (location = 0)` in the vertex shader, this call will link the vertex attribute to the vertex shader.

## Create a vertex shader

### Coding the vertex shader

A vertex shader is a small program that runs on the GPU. Its job is to transform the 3D coordinates of each vertex into 2D coordinates on the screen. The vertex shader is the first stage of the graphics pipeline.

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
```

* `#version 330 core`: specifies the version of the shader. We are using OpenGL 3.3 so we set its version to 330.
* `layout (location = 0) in vec3 aPos`: specifies the vertex attribute location for the position vector and its type.
* `gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0)`: sets the position of the vertex in clip coordinates. The clip coordinates are a special coordinate space that is used by OpenGL after the vertex shader has run. All coordinates that are between -1 and 1 in each dimension will be visible on your screen. The `w` component is used in perspective division and is explained later.

### Compiling the vertex shader

We need to compile the vertex shader before we can use it. We do this by creating a shader object, attaching the shader source code to the object, and then compiling the shader. OpenGL performs the compilation during run-time.

Assuming that we created a `shaders/` folder, and stored the vertex shader in `shaders/vertex.vert`, we can compile the shader as follows:

```cpp
std::string vertexShaderSource = readFile("shaders/vertex.vert");
const char* vertexShaderSourceCStr = vertexShaderSource.c_str();

unsigned int vertexShader;
vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, NULL);
glCompileShader(vertexShader);
```

> `ReadFile` can be any user-defined function that reads a file and returns its contents as a string.

* `glCreateShader(GL_VERTEX_SHADER)`: creates a shader object and returns its ID. The argument specifies the type of shader we want to create. We want to create a vertex shader so we pass `GL_VERTEX_SHADER
* `glShaderSource(vertexShader, 1, &vertexShaderSourceCStr, NULL)`: sets the source code in the shader object. The second argument specifies how many strings we want to pass as source code. The third argument is the actual source code of the vertex shader. The fourth argument is an array of string lengths. Passing `NULL` means that the strings are null-terminated.

### Error handling

We can check if the compilation was successful by calling `glGetShaderiv` with the `GL_COMPILE_STATUS` parameter. If the compilation failed, we can retrieve the error message by calling `glGetShaderInfoLog`.

```cpp
int success;
char infoLog[512];
glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
if (!success)
{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
}
```

## Create a fragment shader

### Coding the fragment shader

A fragment shader is a small program that runs on the GPU. Its job is to calculate the color of each pixel that the triangle covers. The fragment shader is the last stage of the graphics pipeline.

```glsl
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
```

* `#version 330 core`: specifies the version of the shader. We are using OpenGL 3.3 so we set its version to 330.
* `out vec4 FragColor`: specifies the output variable of the fragment shader. The fragment shader is required to set the color of each pixel to this variable.

### Compiling the fragment shader

We need to compile the fragment shader before we can use it. We do this by creating a shader object, attaching the shader source code to the object, and then compiling the shader. OpenGL performs the compilation during run-time.

Assuming that we created a `shaders/` folder, and stored the fragment shader in `shaders/fragment.frag`, we can compile the shader as follows:

```cpp
std::string fragmentShaderSource = readFile("shaders/fragment.frag");
const char* fragmentShaderSourceCStr = fragmentShaderSource.c_str();

unsigned int fragmentShader;
fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource(fragmentShader, 1, &fragmentShaderSourceCStr, NULL);
glCompileShader(fragmentShader);
```

The steps are the same as for the vertex shader.

## Create a shader program

Now that we have compiled the vertex and fragment shaders, we need to link them into a shader program. A shader program is a collection of shaders that are linked together. The shader program is the final linked version of multiple shaders combined. It is the one that is used for rendering.

```cpp
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```

We can check if the linking is successful by calling `glGetProgramiv` with the `GL_LINK_STATUS` parameter. If the linking failed, we can retrieve the error message by calling `glGetProgramInfoLog`.

```cpp
int success;
char infoLog[512];
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}
```

We can delete the shader objects now that we have linked them into a shader program.

```cpp
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```

## Use the shader program and draw the triangle

We can now use the shader program to draw the triangle. We do this by calling `glUseProgram` with the shader program as its argument. This tells OpenGL to use this shader program for all subsequent draw calls.

```cpp
while(!glfwWindowShouldClose(window))
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    processInput(window);
    glfwPollEvents();    
    glfwSwapBuffers(window);
}
```
