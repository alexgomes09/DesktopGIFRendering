cmake_minimum_required(VERSION 3.31)
project(DesktopGifRendering)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)

file(GLOB_RECURSE SOURCES
        CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/src/*.cpp
        ${CMAKE_SOURCE_DIR}/lib/*.cpp
        ${CMAKE_SOURCE_DIR}/lib/*.c
)

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(glfw3 3.3 REQUIRED)

target_include_directories(${PROJECT_NAME}
        PRIVATE ${CMAKE_SOURCE_DIR}/lib
)

target_link_libraries(
        ${PROJECT_NAME}
        glfw
        "/usr/local/opt/giflib/lib/libgif.7.2.0.dylib"
#        "-framework AppKit"
#        "-framework IOKit"
)

