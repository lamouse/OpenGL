#pragma once
#include <string_view>
#include <glm/glm.hpp>
namespace render::gl {

    class Shader{

        public:
            Shader(std::string_view vertex, std::string_view fragment);

            void use()const;
            ~Shader();

            void setBool(std::string_view name, bool value) const;
            void setInt(std::string_view name, int value) const;
            void setFloat(std::string_view name, float value) const;
            void setMatrix4fv(std::string_view name, const glm::mat4& mat) const;

            unsigned int ID{};
        private:

    };

}