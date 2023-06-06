cmake_minimum_required(VERSION 3.0.0)
project(Trifle VERSION 0.0.1)
cmake_policy(VERSION 3.0)

set(NAME "Trifle")

set(CMAKE_CXX_STANDARD 17) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

find_package(GLM REQUIRED)
message(STATUS "Found GLM in ${GLM_INCLUDE_DIR}")

find_package(GTest REQUIRED)
message(STATUS "Found GTest in ${GTEST_INCLUDE_DIRS}")

if(WIN32)
set(LIBS opengl32 glfw3 glm)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif (UNIX)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
set(LIBS X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL pthread freetype ${GLFW3_LIBRARY})
set (CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
else()
set(LIBS )
endif(WIN32)

include_directories(${PROJECT_SOURCE_DIR}/includes)

add_subdirectory(Trifle.Game)
add_subdirectory(Trifle.Test)






