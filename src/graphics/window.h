#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
namespace graphics
{
    class Window
    {
    public:
        Window(int width, int height, const std::string& title);
        bool shouldClose() const;
        void pullEvent();
        ~Window();
    private:
        GLFWwindow* m_window;

    };
} // graphics

