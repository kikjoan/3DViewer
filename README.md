# 3DViewer

## Description

**3DViewer** is an educational project designed to visualize and interact with 3D models. The project demonstrates the use of modern rendering techniques and integrates various libraries to provide a robust and responsive user experience.

The application is developed in **C++** and utilizes a combination of **OpenGL**, **GLEW**, **GLFW**, and **Qt6** for rendering and user interface functionalities.

## Build and Run

1. Ensure all required dependencies are installed on your system (see the **Dependencies** section).
2. Use a supported build system (e.g., CMake) to configure the project:
   ```
   sd src
   make all
   ```
3. After a successful build, the executable will be available in the build directory.


## Dependencies

The following libraries are required to build and run the project:

• **OpenGL** (core rendering library)

• **GLEW** (OpenGL Extension Wrangler Library)

• **GLFW** (for managing windows and input)

• **Qt6** (components: Core, Gui, Widgets, OpenGL, OpenGLWidgets, Concurrent)

Ensure these libraries are installed and properly configured in your development environment.

**Notes**

• The project leverages modern OpenGL features; ensure your system supports the required OpenGL version.

• **Qt6** components are used for creating a feature-rich graphical user interface.

• The build process uses find_package to locate dependencies. Verify that your system’s package manager or environment paths include the necessary libraries.
