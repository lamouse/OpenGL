#pragma once
#include <string_view>
namespace render::gl {

    class Shader{

        public:
            Shader(std::string_view vertex, std::string_view fragment);

            void use()const;
            ~Shader();
            unsigned int ID{};
        private:

    };

}