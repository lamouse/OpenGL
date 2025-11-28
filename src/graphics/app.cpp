//
// Created by ziyu on 2025/11/27.
//

#include "app.hpp"
#include "render/gl/render_gl.hpp"
#include "render/gl/gl_common/shader.hpp"
#include "render/gl/gl_common/gl_vertex.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>




namespace graphics {
App::App() : window_(1920, 1080, "OpenGL"), render_base(std::make_unique<render::RenderGL>()) {}

void App::run() {
    std::array clear_color = {.2f, .3f, .3f, 1.f};

    render::gl::Shader shader("triangle.vert", "triangle.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions         // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // top

    };

    render::gl::Vertex vertex;
    vertex.bindVBO(vertices, 3);
    std::array attribute = {render::VertexAttribute{.location = 0,
                                            .size = 3,
                                            .type = GL_FLOAT,
                                            .normalize = GL_FALSE,
                                            .stride = 6 * sizeof(float),
                                            .offset = 0},
                            render::VertexAttribute{.location = 1,
                                            .size = 3,
                                            .type = GL_FLOAT,
                                            .normalize = GL_FALSE,
                                            .stride = 6 * sizeof(float),
                                            .offset = 3 * sizeof(float)}};
    vertex.setVertexAttribute(attribute);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    shader.use();
    while (!window_.shouldClose()) {
        render_base->clear(clear_color);

        vertex.draw();
        window_.pullEvent();
    }
}
App::~App() = default;

}  // namespace graphics