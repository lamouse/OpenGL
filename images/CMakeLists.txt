cmake_minimum_required(VERSION 3.16)


set(IMAGES_SOURCE_DIR ${CMAKE_SOURCE_DIR}/images)
set(IMAGES_OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin/data/images)
file(MAKE_DIRECTORY "${IMAGES_OUTPUT_DIR}")
set(IMAGE_EXTENSIONS jpg png)
set(IMAGE_FILES "")

foreach(ext IN LISTS IMAGE_EXTENSIONS)
    file(GLOB_RECURSE tmp
        LIST_DIRECTORIES false
        RELATIVE "${IMAGES_SOURCE_DIR}"
        CONFIGURE_DEPENDS
        "${IMAGES_SOURCE_DIR}/*.${ext}"
    )
    list(APPEND IMAGE_FILES ${tmp})
endforeach()


set(IMAGE_OUT_PATHS "")
foreach(IMAGE_FILE IN LISTS IMAGE_FILES)
    set(IMAGE_OUT_PATH ${IMAGES_OUTPUT_DIR}/${IMAGE_FILE})
    add_custom_command(
        OUTPUT ${IMAGE_OUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${IMAGES_SOURCE_DIR}/${IMAGE_FILE}" "${IMAGE_OUT_PATH}"
    )
    list(APPEND IMAGE_OUT_PATHS ${IMAGE_OUT_PATH})
endforeach()

add_custom_target(copy_images ALL
    DEPENDS ${IMAGE_OUT_PATHS}
)


set(TEXTURE_ROOT_PATH "data/images/")
set(CUBE_MAP_PATH "data/images/cube/")


set(IMAGE_PATH_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/include PARENT_SCOPE)
set(IMAGE_INCLUDE ${CMAKE_CURRENT_BINARY_DIR}/include)
# 配置模板
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/image_config.hpp.in"
    "${IMAGE_INCLUDE}/image_config.hpp"
    @ONLY
)
