//
// Created by ziyu on 2025/11/27.
//

#include "app.hpp"
#include "render/gl/render_gl.hpp"
#include "render/gl/gl_common/shader.hpp"
#include "render/gl/gl_common/gl_vertex.hpp"
#include "render/gl/gl_texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct MeshVertex {
        glm::vec3 position{};
        glm::vec2 texCoord{};
};

namespace graphics {
App::App() : window_(1920, 1080, "OpenGL"), render_base(std::make_unique<render::RenderGL>()) {}

void App::run() {
    std::array clear_color = {.2f, .3f, .3f, 1.f};

    float vertices[] = {
        // positions          // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  // top right
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f, 0.0f, 1.0f   // top left
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
                                                    .stride = sizeof(MeshVertex),
                                                    .offset = 0},
                            render::VertexAttribute{.location = 1,
                                                    .size = 2,
                                                    .type = GL_FLOAT,
                                                    .normalize = GL_FALSE,
                                                    .stride = sizeof(MeshVertex),
                                                    .offset = offsetof(MeshVertex, texCoord)}};
    vertex.setVertexAttribute(attribute);

    render::gl::Texture texture("base.png");
    render::gl::Texture texture2("base1.jpg");
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    render::gl::Shader shader("5_1.vert", "5_1.frag");
    shader.use();  // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    shader.setInt("texture1", 0);
    // or set it via the texture class
    shader.setInt("texture2", 1);
    while (!window_.shouldClose()) {
        render_base->clear(clear_color);
        // bind Texture
        texture.bind();
        texture2.bind(1);
        // create transformations
        auto transform =
            glm::mat4(1.0f);  // make sure to initialize matrix to identity matrix first
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.use();
        shader.setMatrix4fv("transform", transform);
        vertex.draw();
        window_.pullEvent();
    }
}
App::~App() = default;

}  // namespace graphics