cmake_minimum_required(VERSION 3.28)
project(3DViewer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets Concurrent)

add_executable(3DViewer
        src/engine/parser.cpp src/engine/parser.h
        src/ui/mainwindow.h src/ui/mainwindow.cpp src/ui/mainwindow.ui
        src/main.cpp
        src/engine/renderer.cpp src/engine/renderer.h
        src/engine/camera_controller/cameraController.cpp src/engine/camera_controller/cameraController.h
        src/engine/controller.h
        src/misc/datatype.h
        src/engine/settingsEditor.h
        src/ui/settingsWidget.h src/ui/settingsWidget.cpp src/ui/settingsWidget.ui
)


FILE(COPY ./src/shaders DESTINATION .)
FILE(COPY ./src/misc/settings.conf DESTINATION .)

target_link_libraries(3DViewer PRIVATE glfw Qt6::Core Qt6::Widgets Qt6::OpenGL OpenGL::GL GLEW::GLEW OpenGL::GLU Qt6::Gui Qt6::OpenGLWidgets Qt6::Concurrent)

add_subdirectory(src/tests)

install(TARGETS 3DViewer DESTINATION .)
install(DIRECTORY src/obj/ DESTINATION ./obj)
install(DIRECTORY src/shaders/ DESTINATION ./shaders)




