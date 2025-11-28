#include "render/gl/render_gl.hpp"
#include <glad/glad.h>
namespace render {

    RenderGL::RenderGL(){

    }

    void RenderGL::clear(std::array<float, 4>& clearColor, bool has_depth){
        auto clear = GL_COLOR_BUFFER_BIT;
        if(has_depth){
            clear |= GL_DEPTH_BUFFER_BIT;
        }
        glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
        glClear(clear);
    }

}