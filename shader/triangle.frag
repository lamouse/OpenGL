#version 450 core
layout(location = 0) out vec4 FragColor;
layout(set = 0, binding = 0) uniform InColor {
    vec4 color;
} ubo;
void main()
{
    FragColor = vec4(ubo.color);
}