#version 450

in vec2 TexCoord;
out vec4 FragData;

uniform sampler2D tex1;

void main()
{
    FragData = texture(tex1, TexCoord);
}
