cmake_minimum_required(VERSION 4.0)
project(OpenGL)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 26)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Executable output path")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE PATH "Library output path")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib CACHE PATH "Single Directory for all static libraries.")
set(BUILD_TESTING ON)

if(NOT CMAKE_GENERATOR STREQUAL "Ninja")
    message(FATAL_ERROR "This project requires the Ninja generator. Refers to https://cmake.org/cmake/help/latest/manual/cmake-cxxmodules.7.html#generator-support")
endif()

if(NOT $ENV{VCPKG_ROOT} STREQUAL "")
    if("${CMAKE_TOOLCHAIN_FILE}" STREQUAL "")
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
        option(VCPKG_MANIFEST_MODE "")
        include("${CMAKE_TOOLCHAIN_FILE}")
    else()
        option(VCPKG_MANIFEST_MODE "")
        include("${CMAKE_TOOLCHAIN_FILE}")
    endif()
else()
    if(NOT "$ENV{VCPKG_TOOLCHAIN_FILE}" STREQUAL "")
        # Disable manifest mode (use vcpkg classic mode) when using a custom vcpkg installation
        option(VCPKG_MANIFEST_MODE "")
        include("$ENV{VCPKG_TOOLCHAIN_FILE}")
    endif()

    if(NOT ${CMAKE_TOOLCHAIN_FILE} STREQUAL "")
        option(VCPKG_MANIFEST_MODE "")
        include("${CMAKE_TOOLCHAIN_FILE}")
    endif()
endif()

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(Stb REQUIRED)

add_subdirectory(shader)
add_subdirectory(images)

add_subdirectory(src)

