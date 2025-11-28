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

    float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
                        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

                        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
                        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

                        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
                        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

                        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
                        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
                        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
                        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

                        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
                        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {glm::vec3(0.0f, 0.0f, 0.0f),    glm::vec3(2.0f, 5.0f, -15.0f),
                                 glm::vec3(-1.5f, -2.2f, -2.5f), glm::vec3(-3.8f, -2.0f, -12.3f),
                                 glm::vec3(2.4f, -0.4f, -3.5f),  glm::vec3(-1.7f, 3.0f, -7.5f),
                                 glm::vec3(1.3f, -2.0f, -2.5f),  glm::vec3(1.5f, 2.0f, -2.5f),
                                 glm::vec3(1.5f, 0.2f, -1.5f),   glm::vec3(-1.3f, 1.0f, -1.5f)};

    render::gl::Vertex vertex;
    vertex.bindVBO(vertices, 36);
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
     glEnable(GL_DEPTH_TEST);
    render::gl::Shader shader("6_3.vert", "6_3.frag");
    shader.use();  // don't forget to activate/use the shader before setting uniforms!
    // either set it manually like so:
    shader.setInt("texture1", 0);
    // or set it via the texture class
    shader.setInt("texture2", 1);

    while (!window_.shouldClose()) {
        render_base->clear(clear_color, true);
        // bind Texture
        texture.bind();
        texture2.bind(1);

        shader.use();

        auto view = glm::mat4(1.0f);  // make sure to initialize matrix to identity matrix first
        auto projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)1920 / (float)1080, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        // pass transformation matrices to the shader
        shader.setMatrix4fv(
            "projection",
            projection);  // note: currently we set the projection matrix each frame, but
                          // since the projection matrix rarely changes it's often best
                          // practice to set it outside the main loop only once.
        shader.setMatrix4fv("view", view);
        vertex.bindVertexArray();
        for (unsigned int i = 0; i < 10; i++) {
            // calculate the model matrix for each object and pass it to shader before drawing
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader.setMatrix4fv("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
            vertex.draw();
        }

        window_.pullEvent();
    }
}
App::~App() = default;

}  // namespace graphics