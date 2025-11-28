//
// Created by ziyu on 2025/11/27.
//

#include "app.hpp"
#include "render/gl/render_gl.hpp"
#include "render/gl/gl_common/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Vertex {
    public:
        Vertex() {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
        }

        void bindVertexArray() const { glBindVertexArray(VAO); }
        ~Vertex() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
        }
        unsigned int VAO{};
        unsigned int VBO{};
        unsigned EBO{};

    private:
};
namespace graphics {
App::App() : window_(1920, 1080, "OpenGL"), render_base(std::make_unique<render::RenderGL>()) {}

void App::run() {
    std::array clear_color = {.2f, .3f, .3f, 1.f};

    render::gl::Shader shader("triangle.vert", "triangle.frag");

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f   // top left
    };
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };

    Vertex vertex;

    glBindBuffer(GL_ARRAY_BUFFER, vertex.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    GLuint blockIndex = glGetUniformBlockIndex(shader.ID, "InColor");

    glm::vec4 myColor{1.f};

    GLuint uboHandle{};
    glGenBuffers(1, &uboHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), glm::value_ptr(myColor), GL_DYNAMIC_DRAW);

    while (!window_.shouldClose()) {
        render_base->clear(clear_color);

        auto timeValue = static_cast<float>(glfwGetTime());
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        myColor.y = greenValue;

        // 更新 UBO 数据
        glBindBuffer(GL_UNIFORM_BUFFER, uboHandle);
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec4), glm::value_ptr(myColor));
        glBindBuffer(GL_UNIFORM_BUFFER, 0);

        GLuint bindingPoint = 0;  // 对应 layout(binding = 0)
        glUniformBlockBinding(shader.ID, blockIndex, bindingPoint);
        // 绑定到 binding point
        glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, uboHandle);

        shader.use();
        vertex.bindVertexArray();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window_.pullEvent();
    }

}
App::~App() = default;

}  // namespace graphics