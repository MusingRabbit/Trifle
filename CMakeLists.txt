cmake_minimum_required(VERSION 3.0.0)
project(Trifle VERSION 0.0.1)
cmake_policy(VERSION 3.0)

set(NAME "Trifle")

set(CMAKE_CXX_STANDARD 20) # this does nothing for MSVC, use target_compile_options below
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/modules)
set(LIB_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /STACK:10000000")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

#[===[
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

find_package(GLM REQUIRED)
message(STATUS "Found GLM in ${GLM_INCLUDE_DIR}")

find_package(GTest REQUIRED)
message(STATUS "Found GTest in ${GTEST_INCLUDE_DIRS}")
]===]
find_package(Threads)

set(LIBS freetyped)

if(WIN32)
    find_package(dbghelp REQUIRED)
    message(STATUS "Found Dbghelp in ${DBGHELP_LIBRARY}")

    set(LIBS ${LIBS} glfw3 opengl32 glm dbghelp glew)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(UNIX)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
    find_package(OpenGL REQUIRED)
    add_definitions(${OPENGL_DEFINITIONS})
    set(LIBS ${LIBS} X11 Xrandr Xinerama Xi Xxf86vm Xcursor GL pthread glew)
    set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")
else()
    set(LIBS ${LIBS})
endif(WIN32)

include_directories(
    ${LIB_DIRECTORY}/glew/include
    ${LIB_DIRECTORY}/glfw/include
    ${LIB_DIRECTORY}/glm/include
    ${LIB_DIRECTORY}/freetype/include
    ${LIB_DIRECTORY}/gtest/include
)

link_directories(
    ${LIB_DIRECTORY}/glew/lib
    ${LIB_DIRECTORY}/glfw/lib
    ${LIB_DIRECTORY}/glm/lib
    ${LIB_DIRECTORY}/freetype/lib
    ${LIB_DIRECTORY}/gtest/lib/Debug
)

#[===[
include_directories(${PROJECT_SOURCE_DIR}/includes)
]===]
add_subdirectory(Trifle.Engine)
add_subdirectory(Trifle.Game)
add_subdirectory(Trifle.Test)
