set(GAME_NAME ${NAME}.Game)
set(GAME_SOURCE_DIR "${PROJECT_SOURCE_DIR}/${GAME_NAME}/src")

set(ENGINE_NAME ${NAME}.Engine)

message(STATUS "GAME_SOURCE_DIR = ${GAME_SOURCE_DIR}")

file(GLOB_RECURSE SOURCE_FILES
    ${GAME_SOURCE_DIR}/*.c
    ${GAME_SOURCE_DIR}/*.cpp
    ${GAME_SOURCE_DIR}/*.h
    ${GAME_SOURCE_DIR}/*.hpp
)

message(STATUS "LIBS = ${LIBS}")
message(STATUS "OPENGL_INCLUDE_DIR = ${OPENGL_INCLUDE_DIR}")
message(STATUS "ENGINE_NAME = ${ENGINE_NAME}")

add_executable(${GAME_NAME} ${SOURCE_FILES})
target_include_directories(${GAME_NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${GAME_NAME} ${LIBS})
target_link_libraries(${GAME_NAME} ${ENGINE_NAME})
