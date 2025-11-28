#define STB_IMAGE_IMPLEMENTATION
#include "resource/texture.hpp"
#include <stb_image.h>
#include <stdexcept>
#include "image_config.hpp"
namespace graphics::resource {

Texture::Texture(std::string_view name) {
    stbi_set_flip_vertically_on_load(true);
    data_ = stbi_load((std::string(texture::TEXTURE_ROOT_PATH) + std::string(name)).c_str(), &width_,
                    &hight_, &channels, STBI_rgb_alpha);
    if (!data_) {
        throw ::std::runtime_error("failed to load texture image!");
    }
    map_data = std::span<unsigned char>(data_, size());
}

Texture::~Texture() {
    if (data_) {
        stbi_image_free(data_);
    }
}

}  // namespace graphics::resource