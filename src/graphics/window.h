#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "graphics/camera.hpp"
namespace graphics
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        [[nodiscard]] auto shouldClose() const -> bool;
        void pullEvent();
        auto getCamera() ->Camera&;
        ~Window();
    private:
        GLFWwindow* m_window;
    };
} // graphics

