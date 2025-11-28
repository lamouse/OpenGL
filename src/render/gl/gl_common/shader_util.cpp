#include "render/gl/gl_common/shader_util.hpp"
#include "source_shader.h"
#include <print>
#include <filesystem>
#include <fstream>
#include <glad/glad.h>

namespace {
auto readFileToString(const std::filesystem::path& file) -> std::string {
    std::ifstream ifs(file, std::ios::binary | std::ios::ate);
    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file: " + file.string());
    }

    std::streamsize size = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::string buffer(size, '\0');
    if (!ifs.read(buffer.data(), size)) {
        throw std::runtime_error("Failed to read file: " + file.string());
    }

    return buffer;
}

void check_build(unsigned int shader) {
    int success{};
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);//NOLINT
        std::println("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n {}", infoLog);
        throw std::runtime_error("Failed to open file: " + std::string(infoLog));//NOLINT
    }
}
}

namespace render::gl {
auto build_shader(std::string_view shader_name) -> unsigned int {
    namespace fs = std::filesystem;
    unsigned int shader = 0;
    fs::path file(std::string(shader::SHADER_ROOT_PATH) + std::string(shader_name));
    if (!fs::exists(file)) {
        std::println("file not exists {}", file.string());
        return shader;
    }

    if (!fs::is_regular_file(file)) {
        std::println("file is not regular file {}", file.string());
        return shader;
    }

    const auto shader_source = readFileToString(file);
    auto file_ext = file.extension();
    if (file_ext == shader::VERTEX_SHADER_EXTENSION) {
        shader = glCreateShader(GL_VERTEX_SHADER);
    } else if (file_ext == shader::FRAGMENT_SHADER_EXTENSION) {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    } else if (file_ext == shader::COMPUTE_SHADER_EXTENSION) {
        shader = glCreateShader(GL_COMPUTE_SHADER);
    } else {
        std::println("unknow shader type {}", file_ext.string());
        return shader;
    }
    const char* source_ptr = shader_source.c_str();
    glShaderSource(shader, 1, &source_ptr, nullptr);
    glCompileShader(shader);
    check_build(shader);
    return shader;
}
}