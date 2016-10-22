cmake_minimum_required(VERSION 3.5)
project(OpenGL1)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp tor.hpp utils.hpp cone.hpp cone.cpp figure.cpp figure.hpp tor.cpp sphere.cpp sphere.hpp cylinder.cpp cylinder.hpp morpher.cpp morpher.hpp)


find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)

add_executable(OpenGL1 ${SOURCE_FILES})
target_link_libraries(OpenGL1 glfw3 GL GLU X11 m dl Xxf86vm Xi pthread Xrandr Xinerama Xcursor)

