#pragma once
#include "window.h"
#include "common/common_funcs.hpp"
#include <memory>
namespace render {
    class RenderBase;
}
namespace graphics
{
    class App
    {
        public:
            App();
            CLASS_DEFAULT_MOVEABLE(App);
            CLASS_NON_COPYABLE(App);
            ~App();
            void run();
        private:
            Window window_;
            std::unique_ptr<render::RenderBase> render_base;
    };
} // app

