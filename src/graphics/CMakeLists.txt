
set(PROGRAM_NAME "OpenGL")
include(${CMAKE_CURRENT_SOURCE_DIR}/graphics.cmake)
add_executable(${PROGRAM_NAME} ${sources})
target_link_libraries(${PROGRAM_NAME} glfw glm::glm render)