#include "resource/texture.hpp"
#include <stb_image.h>
#include <stdexcept>
namespace graphics::resource {

Texture::Texture(std::string_view name)
    : data_(stbi_load(name.data(), &width_, &hight_, &channels, STBI_rgb_alpha)) {
    if (!data_) {
        throw ::std::runtime_error("failed to load texture image!");
    }
    map_data = std::span<unsigned char>(data_, size());
}

Texture::~Texture(){
    if (data_) {
       stbi_image_free(data_);
    }
}

}  // namespace graphics::resource