#include "render/gl/gl_common/shader.hpp"
#include "render/gl/gl_common/shader_util.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <print>
namespace render::gl {
Shader::Shader(std::string_view vertex, std::string_view fragment) : ID(glCreateProgram()) {
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

void Shader::use() const { glUseProgram(ID); }

void Shader::setBool(std::string_view name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.data()), value);
}
void Shader::setInt(std::string_view name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.data()), value);
}
void Shader::setFloat(std::string_view name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.data()), value);
}

void Shader::setMatrix4fv(std::string_view name, const glm::mat4& mat)const{
        glUniformMatrix4fv(glGetUniformLocation(ID, name.data()), 1, GL_FALSE, glm::value_ptr(mat));
}
Shader::~Shader() { glDeleteProgram(ID); }

}  // namespace render::gl