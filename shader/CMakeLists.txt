cmake_minimum_required(VERSION 3.16)


set(SHADER_SOURCE_DIR ${CMAKE_SOURCE_DIR}/shader)
set(SHADER_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/data/shader)
file(MAKE_DIRECTORY "${SHADER_OUTPUT_DIR}")
set(SHADER_EXTENSIONS vert frag comp)
set(SHADER_FILES "")

foreach(ext IN LISTS SHADER_EXTENSIONS)
    file(GLOB_RECURSE tmp
        LIST_DIRECTORIES false
        RELATIVE "${SHADER_SOURCE_DIR}"
        CONFIGURE_DEPENDS
        "${SHADER_SOURCE_DIR}/*.${ext}"
    )
    list(APPEND SHADER_FILES ${tmp})
endforeach()


set(SHADER_OUT_PATHS "")
foreach(SHADER_FILE IN LISTS SHADER_FILES)
    set(SHADER_OUT_PATH ${SHADER_OUTPUT_DIR}/${SHADER_FILE})
    add_custom_command(
        OUTPUT ${SHADER_OUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SHADER_SOURCE_DIR}/${SHADER_FILE}" "${SHADER_OUT_PATH}"
        DEPENDS "${SHADER_SOURCE_DIR}/${SHADER_FILE}"
    )
    list(APPEND SHADER_OUT_PATHS ${SHADER_OUT_PATH})
endforeach()

add_custom_target(copy_shaders ALL
    DEPENDS ${SHADER_OUT_PATHS}
)


set(SHADER_PATH "data/shader/")
set(VERTEX_SHADER_EXTENSION ".vert")
set(FRAGMENT_SHADER_EXTENSION ".frag")
set(COMPUTE_SHADER_EXTENSION ".comp")

set(SHADER_PATH_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/include PARENT_SCOPE)
set(SHADER_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/include)
# 配置模板
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/source_shader.h.in"
    "${SHADER_INCLUDE}/source_shader.h"
    @ONLY
)
