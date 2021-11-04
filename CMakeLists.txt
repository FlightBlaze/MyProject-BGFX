cmake_minimum_required (VERSION 3.8)

project ("MyProject")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source to this project's executable.

add_executable (MyProject "MyProject.cpp")

target_include_directories(MyProject PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

# Copy assets to the binary directory

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/assets/")

# SDL

option(SDL_METAL "" ON)
add_subdirectory("submodules/SDL")
target_include_directories(MyProject PRIVATE "submodules/SDL/include")
target_link_libraries(MyProject SDL2-static)

# GLFW

add_subdirectory("submodules/glfw")
target_include_directories(MyProject PRIVATE "submodules/glfw/include")
target_link_libraries(MyProject glfw)

# BGFX

find_library(METAL Metal REQUIRED)
find_library(COCOA Cocoa REQUIRED)
find_library(QUARTZ_CORE QuartzCore REQUIRED)

target_include_directories(MyProject PRIVATE "submodules/bgfx/include" "submodules/bx/include")
target_link_directories(MyProject PRIVATE "submodules/bgfx/.build/osx-arm64/bin")
target_link_libraries(MyProject bgfxDebug bimgDebug bxDebug ${METAL} ${COCOA} ${QUARTZ_CORE})
