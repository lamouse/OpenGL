#pragma once
#include <array>
namespace render {
    class RenderBase{
        public:
        RenderBase();
        virtual void clear(std::array<float, 4>& clearColor, bool has_depth = false) = 0;
        virtual ~RenderBase() = default;
    };
}