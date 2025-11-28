//
// Created by ziyu on 2025/11/27.
//

#include "window.h"
#include <print>

namespace {
// process all input: query GLFW whether relevant keys are pressed/released this frame and react
// accordingly
// ---------------------------------------------------------------------------------------------------------

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* /*window*/, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

graphics::Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 1920 / 2.0f;
float lastY = 1080 / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;  // time between current frame and last frame
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;  // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(graphics::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(graphics::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(graphics::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(graphics::RIGHT, deltaTime);
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
    glfwSetCursorPosCallback(m_window, mouse_callback);
    glfwSetScrollCallback(m_window, scroll_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // 设置窗口最小尺寸为 160x90
    glfwSetWindowSizeLimits(m_window, 160, 90, GLFW_DONT_CARE, GLFW_DONT_CARE);
    // NOLINTNEXTLINE
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::println("Failed to initialize GLAD");
    }
}
auto Window::shouldClose() const -> bool { return glfwWindowShouldClose(m_window); }
void Window::pullEvent() {
    glfwSwapBuffers(m_window);
    processInput(m_window);
    ::glfwPollEvents();
    // per-frame time logic
    // --------------------
    auto currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
}
Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }
}
auto Window::getCamera() -> Camera& { return camera; }
}  // namespace graphics