cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(sdl3-lib-app
    VERSION 1.0.0
    DESCRIPTION "Basic template for a modern cmake-c++-sdl3-library with application"
    LANGUAGES CXX
)

set(WORKSPACE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(WORKSPACE_BINARY_DIR "${WORKSPACE_DIR}/bin/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")
set(WORKSPACE_ARTIFACT_DIR "${WORKSPACE_DIR}/bin-int/${CMAKE_SYSTEM_NAME}-${CMAKE_BUILD_TYPE}")

# prevent installation to system directory
set(CMAKE_INSTALL_PREFIX "${WORKSPACE_BINARY_DIR}" CACHE INTERNAL "")

option(BUILD_SHARED "Build lib as shared" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Options)
include(Dependencies)

add_subdirectory(src)
add_subdirectory(app)
