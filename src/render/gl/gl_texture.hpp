#pragma once
#include <string_view>
namespace render::gl {
class Texture {
    public:
        Texture(std::string_view name);
        void bind() const;
    private:
        unsigned int texture{};
};
}  // namespace render::gl