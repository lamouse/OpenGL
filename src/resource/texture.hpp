#pragma once
#include <string_view>
#include <span>
namespace graphics::resource {
class Texture {
        Texture(std::string_view name);
        [[nodiscard]] auto width() const -> int { return width_; }
        [[nodiscard]] auto height() const -> int { return hight_; }
        ~Texture();

    private:
        [[nodiscard]] auto size() const -> unsigned long long { return width_ * hight_ * channels; }
        int width_{};
        int hight_{};
        unsigned char* data_{nullptr};
        int channels = 0;
        std::span<unsigned char> map_data;
};

}  // namespace graphics::resource