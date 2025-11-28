#pragma once
#include "render/vertex.hpp"
#include "render/gl/gl_common/util.hpp"
#include <span>
#include <stdexcept>
#include <string>
namespace render::gl {
    class Vertex {
    public:
        Vertex() {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
        }

        Vertex(const Vertex &) = delete;
        Vertex(Vertex &&) = delete;
        auto operator=(const Vertex &) -> Vertex & = delete;
        auto operator=(Vertex &&) -> Vertex & = delete;
        void bindVertexArray() const { glBindVertexArray(VAO); }
        void bindVBO(std::span<float> vertex, int vertexCount, GLenum usage = GL_STATIC_DRAW) {
            vertex_count = vertexCount;
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(vertex.size() * sizeof(float)),
                         vertex.data(),usage );
        }

        template <typename T>
        void bindEBO(std::span<T> indices, GLenum usage = GL_STATIC_DRAW) {
            if (EBO == 0) {
                glGenBuffers(1, &EBO);  // 按需创建
            }
            index_type = getIndexType<T>();
            index_count = indices.size();
            static_assert(std::is_same_v<T, GLubyte> || std::is_same_v<T, GLushort> ||
                              std::is_same_v<T, GLuint>,
                          "EBO index type must be GLubyte, GLushort, or GLuint");
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(T), indices.data(),
                         usage);
        }

        void setVertexAttribute(std::span<VertexAttribute> attributes) const {
            glBindVertexArray(VAO);
            for (const auto &attribute : attributes) {
                glVertexAttribPointer(attribute.location, attribute.size, attribute.type,
                                      attribute.normalize, attribute.stride,
                                      byte_offset(attribute.offset));
                glEnableVertexAttribArray(attribute.location);
            }
        }

        void draw() const {
            if (index_count > 0) {
                bindVertexArray();
                glDrawElements(GL_TRIANGLES, index_count, index_type, byte_offset(0));
            } else {
                if (vertex_count < 0) {
                    throw std::runtime_error("vertex count: " + std::to_string(vertex_count));
                }
                glDrawArrays(GL_TRIANGLES, 0, vertex_count);
            }
        }

        ~Vertex() {
            glDeleteVertexArrays(1, &VAO);
            glDeleteBuffers(1, &VBO);
            if (EBO) {
                glDeleteBuffers(1, &EBO);
            }
        }

    private:
        unsigned int VAO{};
        unsigned int VBO{};
        unsigned EBO{};
        GLenum index_type{};

        int vertex_count{};
        int index_count{};
};
}