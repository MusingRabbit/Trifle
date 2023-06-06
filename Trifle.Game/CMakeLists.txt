set (NAME ${NAME}.Game)
set (GAME_SOURCE_DIR "${PROJECT_SOURCE_DIR}/${NAME}/src/")

message(STATUS "GAME_SOURCE_DIR = ${GAME_SOURCE_DIR}")

file(GLOB_RECURSE SOURCE_FILES
${GAME_SOURCE_DIR}*.c
${GAME_SOURCE_DIR}*.cpp
${GAME_SOURCE_DIR}*.h
${GAME_SOURCE_DIR}*.hpp
)

add_executable(${NAME} ${SOURCE_FILES})
target_include_directories(${NAME} PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(${NAME} ${LIBS})


