#pragma once
#include <string_view>
namespace render::gl {

    class Shader{

        public:
            Shader(std::string_view vertex, std::string_view fragment);

            void use()const;
            ~Shader();

            void setBool(std::string_view name, bool value) const;
            void setInt(std::string_view name, int value) const;
            void setFloat(std::string_view, float value) const;

            unsigned int ID{};
        private:

    };

}