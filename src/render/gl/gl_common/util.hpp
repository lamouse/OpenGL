#pragma once
#include <glad/glad.h>
#include <type_traits>
namespace render::gl {
inline auto byte_offset(unsigned int offset) -> const void * {
    return reinterpret_cast<const void *>(offset);
}

template <typename T>
auto getIndexType() -> GLenum {
    if constexpr (std::is_same_v<T, uint8_t>) {
        return GL_UNSIGNED_BYTE;
    } else if constexpr (std::is_same_v<T, uint16_t>) {
        return GL_UNSIGNED_SHORT;
    } else if constexpr (std::is_same_v<T, uint32_t>) {
        return GL_UNSIGNED_INT;
    } else {
        static_assert(sizeof(T) == 0, "Unsupported index type");
    }
}

}