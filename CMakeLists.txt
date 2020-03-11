cmake_minimum_required(VERSION 3.15)
project(GLFWClion)

set(CMAKE_CXX_STANDARD 11)

# Define GLEW_STATIC because the DLL isn't being used
add_compile_definitions(GLEW_STATIC)

# Set the library directory
link_directories(lib)
set(OpenGLLibs glew32s glfw3 opengl32)

# Set the include header directory
include_directories(include)

# In case to use DLL file
# add_custom_target(addGLFW COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/lib/glfw3.dll ${CMAKE_BINARY_DIR})
# add_dependencies(GLFWClion addGLFW)

add_executable(GLFWClion main.cpp)

target_link_libraries(GLFWClion ${OpenGLLibs})

