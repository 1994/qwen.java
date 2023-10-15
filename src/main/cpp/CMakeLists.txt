cmake_minimum_required(VERSION 3.12)
project(qwen-java VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE STRING "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE STRING "")

set(CMAKE_CXX_STANDARD 23)
# fPIC linux独有？
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -fPIC")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

add_subdirectory(qwen.cpp)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(ggml PRIVATE -fPIC)
    include_directories(include/jni-linux)
    include_directories(include/jni-linux/linux)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    include_directories(include/jni-macos)
    include_directories(include/jni-macos/darwin)
else()
    message("unsupported platform")
    return()
endif()

add_library(qwen-java SHARED
        io_github_qwen_Qwen.h
        io_github_qwen_Qwen.cpp
        ObjectCache.h)
target_link_libraries(qwen-java PUBLIC qwen)