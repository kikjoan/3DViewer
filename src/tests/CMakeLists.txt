cmake_minimum_required(VERSION 3.28)
project(3DViewerTest_Test LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(CodeCoverage)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets OpenGL OpenGLWidgets)
find_package(GTest REQUIRED)
enable_testing()

#add_compile_options(-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment)
#add_link_options(-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment)


append_coverage_compiler_flags()

add_executable(3DViewerTest
        parser_tests.cpp engine_tests.cpp
        ../engine/parser.cpp ../engine/parser.h
        ../engine/renderer.cpp ../engine/renderer.h
        ../engine/camera_controller/cameraController.cpp ../engine/camera_controller/cameraController.h
        ../engine/controller.h
        ../misc/datatype.h
)

setup_target_for_coverage_lcov(
        NAME coverage
        EXECUTABLE 3DViewerTest
        DEPENDENCIES 3DViewerTest
        LCOV_ARGS --ignore-errors mismatch,inconsistent,unused
        EXCLUDE "/c++/*" "/usr/*" "/usr/local/include/*" "/14/*" "build*" "../engine/renderer.*"
)

FILE(COPY ../shaders DESTINATION .)
FILE(COPY ../misc/settings.conf DESTINATION .)
FILE(COPY ../obj DESTINATION .)

target_link_libraries(3DViewerTest PRIVATE glfw Qt6::Core Qt6::Widgets Qt6::OpenGL OpenGL::GL GLEW::GLEW OpenGL::GLU Qt6::Gui Qt6::OpenGLWidgets GTest::GTest GTest::Main pthread)

gtest_discover_tests(3DViewerTest)



