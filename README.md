# GLFW Example

### Toolchains configuration

This project use the Visual Studio 2013 (VC12) toolchain, it must be installed aside CLion.

The architecture is for `x86` platform. 

### Libraries

In this sample, its being used the following libraries:
- [**GLFW: an OpenGL library**](https://www.glfw.org/download.html);
- [**GLEW: The OpenGL Extension Wrangler Library**](http://glew.sourceforge.net/);

Both of them is their 32-bits version. Special case for GLFW, that must be used VC12 library version.

All libraries files are in `/lib` folder.

- `glew32s.lib`: GLEW static library file
- `glfw3.lib`: GLFW static library file

The **CMake** command to link these library files is:

```cmake
link_directories(lib)
set(OpenGLLibs glew32s glfw3 opengl32)
target_link_libraries(GLFWClion ${OpenGLLibs})
```

> The default for GLEW commands is to use the _dynamic library_ (*.dll), because this, an additional definition must be in **CMake** file:
> ```cmake
> # Define GLEW_STATIC because the DLL isn't being used
> add_compile_definitions(GLEW_STATIC)
> ``` 

### Headers

The library headers must be in `/include` folder, they are:
- **GLEW/eglew.h**
- **GLEW/glew.h**
- **GLEW/glxew.h**
- **GLEW/wglew.h**
- **GLFW/glfw3.h**
- **GLFW/glfw3native.h**

The **CMake** command to add include folder is:
```cmake
include_directories(include)
```
