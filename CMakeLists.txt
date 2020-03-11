cmake_minimum_required(VERSION 3.15)
project(GLFWClion)

set(CMAKE_CXX_STANDARD 11)
# Define GLEW_STATIC because the DLL isn't being used
add_compile_definitions(GLEW_STATIC)

link_directories(lib)
include_directories(include)

add_custom_target(addGLFW COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/lib/glfw3.dll ${CMAKE_BINARY_DIR})

set(OpenGLLibs glew32s glfw3 glfw3dll opengl32)

add_executable(GLFWClion main.cpp)

target_link_libraries(GLFWClion ${OpenGLLibs})

add_dependencies(GLFWClion addGLFW)