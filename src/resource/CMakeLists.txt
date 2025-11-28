include(${CMAKE_CURRENT_SOURCE_DIR}/resources.cmake)

set(LIB_NAME resources)

add_library(${LIB_NAME} ${sources})
add_dependencies(${LIB_NAME} copy_images)
target_include_directories(${LIB_NAME} PRIVATE ${IMAGE_PATH_INCLUDE})
target_include_directories(${LIB_NAME}  PRIVATE ${Stb_INCLUDE_DIR})
