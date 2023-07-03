#version 330 core
layout (location = 0) in vec3 aPos;

uniform float dx;
uniform float dy;

void main()
{
    gl_Position = vec4(aPos.x + dx, aPos.y + dy, 0, 1.0);
}