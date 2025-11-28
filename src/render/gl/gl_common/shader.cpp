#include "render/gl/gl_common/shader.hpp"
#include "render/gl/gl_common/shader_util.hpp"
#include <glad/glad.h>
#include <print>
namespace render::gl {
Shader::Shader(std::string_view vertex, std::string_view fragment):ID(glCreateProgram()) {
    auto vertex_shader = build_shader(vertex);
    auto fragment_shader = build_shader(fragment);

    glAttachShader(ID, vertex_shader);
    glAttachShader(ID, fragment_shader);
    glLinkProgram(ID);
    int success{};
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::println("link shader error {}", infoLog);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::use()const  { glUseProgram(ID); }

Shader::~Shader(){
        glDeleteProgram(ID);
}

}  // namespace render::gl