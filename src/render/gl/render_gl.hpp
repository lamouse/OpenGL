#include "render/render_base.hpp"

namespace render {

    class RenderGL : public RenderBase{
        public:
        RenderGL();
        ~RenderGL() = default;
        void clear(std::array<float, 4>& clearColor, bool has_depth = false) override;
    };

}
