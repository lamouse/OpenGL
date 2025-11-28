//
// Created by ziyu on 2025/11/27.
//

#include "window.h"
#include <print>

namespace {
// process all input: query GLFW whether relevant keys are pressed/released this frame and react
// accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

}  // namespace

namespace graphics {
Window::Window(int width, int height, const std::string& title) {
    ::glfwInit();
    ::glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    m_window = ::glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);  // NOLINT
    if (!m_window) {
        ::glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    // 设置窗口最小尺寸为 160x90
    glfwSetWindowSizeLimits(m_window, 160, 90, GLFW_DONT_CARE, GLFW_DONT_CARE);
    //NOLINTNEXTLINE
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD");
    }
}
auto Window::shouldClose() const -> bool { return glfwWindowShouldClose(m_window); }
void Window::pullEvent() {
    glfwSwapBuffers(m_window);
    processInput(m_window);
    ::glfwPollEvents();
}
Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}
}  // namespace graphics