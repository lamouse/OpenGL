#include "render/gl/gl_texture.hpp"
#include "resource/texture.hpp"
#include <glad/glad.h>
namespace render::gl {

Texture::Texture(std::string_view name) {
    graphics::resource::Texture image{name};
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, image.data().data());
    glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::bind(uint8_t binding) const {
    if(binding){
        glActiveTexture(GL_TEXTURE0 + binding);
    }
    glBindTexture(GL_TEXTURE_2D, texture);
}
}  // namespace render::gl