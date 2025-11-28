#include "render/gl/render_gl.hpp"
#include <glad/glad.h>
namespace render {

    RenderGL::RenderGL(){

    }

    void RenderGL::clear(std::array<float, 4>& clearColor){
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }

}