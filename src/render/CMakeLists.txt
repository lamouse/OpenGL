include(${CMAKE_CURRENT_SOURCE_DIR}/render.cmake)

set(LIB_NAME render)

add_library(${LIB_NAME} ${sources})
target_link_libraries(${LIB_NAME} PUBLIC glad::glad)
add_dependencies(${LIB_NAME} copy_shaders)
target_include_directories(${LIB_NAME} PRIVATE ${SHADER_PATH_INCLUDE})