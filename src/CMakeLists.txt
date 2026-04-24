if (BUILD_SHARED)
    set(_lib_type SHARED)
else ()
    set(_lib_type STATIC)
endif ()

project(mylib)

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_BINARY_DIR "${WORKSPACE_BINARY_DIR}")
set(PROJECT_SOURCE_DIR "${PROJECT_DIR}")

add_library(${PROJECT_NAME} ${_lib_type}
    mylib.cpp
    core/Application.cpp
    utils/Logger.cpp
    utils/Arguments.cpp
)

add_library(mylib::mylib ALIAS ${PROJECT_NAME})

target_compile_definitions(${PROJECT_NAME} PRIVATE
    MYLIB_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    MYLIB_VERSION_MINOR=${PROJECT_VERSION_MINOR}
)

include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME}
    EXPORT_FILE_NAME ${CMAKE_SOURCE_DIR}/include/${PROJECT_NAME}/export.h
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    MYLIB_EXPORTS
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(${PROJECT_NAME} PUBLIC
    "${spdlog_SOURCE_DIR}/include"
)

target_link_libraries(${PROJECT_NAME} PRIVATE project_warnings SDL3::SDL3)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN ON
)
