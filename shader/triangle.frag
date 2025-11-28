#version 450 core

layout(location = 0) in vec3 outColor;

layout(location = 0) out vec4 FragColor;

void main()
{
    FragColor = vec4(outColor, 1.0f);
}