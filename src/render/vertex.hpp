#pragma once
#include <glad/glad.h>
namespace render {
struct VertexAttribute {
        int location{};
        int size{};
        GLenum type{};
        GLboolean normalize{};
        int stride{};
        unsigned int offset{};  // 对应Pointer
};
}