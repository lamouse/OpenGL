//
// Created by ziyu on 2025/11/27.
//

#include "app.hpp"
#include "render/gl/render_gl.hpp"
#include "render/gl/gl_common/shader.hpp"
#include "render/gl/gl_common/gl_vertex.hpp"
#include "render/gl/gl_texture.hpp"
#include "resource/texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace graphics {
App::App() : window_(1920, 1080, "OpenGL"), render_base(std::make_unique<render::RenderGL>()) {}

void App::run() {
    std::array clear_color = {.2f, .3f, .3f, 1.f};

    float vertices[] = {
        //     ---- 位置 ----       ---- 颜色 ----                      - 纹理坐标 -
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // 右上
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // 右下
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 左下
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f   // 左上
    };

    unsigned int indices[] = {
        0, 1, 3,  // first triangle
        1, 2, 3   // second triangle
    };

    render::gl::Vertex vertex;
    vertex.bindVBO(vertices, 3);
    vertex.bindEBO<unsigned int>(indices);
    std::array attribute = {render::VertexAttribute{.location = 0,
                                                    .size = 3,
                                                    .type = GL_FLOAT,
                                                    .normalize = GL_FALSE,
                                                    .stride = 8 * sizeof(float),
                                                    .offset = 0},
                            render::VertexAttribute{.location = 1,
                                                    .size = 3,
                                                    .type = GL_FLOAT,
                                                    .normalize = GL_FALSE,
                                                    .stride = 8 * sizeof(float),
                                                    .offset = 3 * sizeof(float)},
                            render::VertexAttribute{.location = 2,
                                                    .size = 2,
                                                    .type = GL_FLOAT,
                                                    .normalize = GL_FALSE,
                                                    .stride = 8 * sizeof(float),
                                                    .offset = 6 * sizeof(float)}};
    vertex.setVertexAttribute(attribute);

    render::gl::Texture texture("base.png");

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    render::gl::Shader shader("texture_triangle.vert", "texture_triangle.frag");

    while (!window_.shouldClose()) {
        render_base->clear(clear_color);
        // bind Texture
        texture.bind();
        shader.use();
        vertex.draw();
        window_.pullEvent();
    }
}
App::~App() = default;

}  // namespace graphics