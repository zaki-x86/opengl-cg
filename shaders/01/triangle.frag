#version 450 core

in vec3 ourColor;
//in vec2 TexCoord;
out vec4 FragColor;

//uniform vec4 ourColor; // we set this variable in the OpenGL code.

void main()
{
    FragColor = vec4(ourColor, 1.0);
}