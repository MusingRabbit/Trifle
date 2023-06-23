set(ENGINE_NAME ${NAME}.Engine)
set(GAME_NAME ${NAME}.Game)
set(TEST_NAME ${NAME}.Test)

set(TEST_DIR "${PROJECT_SOURCE_DIR}/${TEST_NAME}")

message("TEST_DIR = ${TEST_DIR}")

set(LIBS ${LIBS} gtest)
message(STATUS "LIBS = ${LIBS}")

file(GLOB_RECURSE TEST_SRC_FILES
${TEST_DIR}/*.c
${TEST_DIR}/*.cpp
${TEST_DIR}/*.h
${TEST_DIR}/*.hpp 
)

add_executable(a.out ${TEST_SRC_FILES})

target_link_libraries(a.out glfw ${GLFW_LIBRARIES} GLEW)
target_link_libraries(a.out ${ENGINE_NAME})
target_link_libraries(a.out ${GTEST_LIBRARIES})
target_link_libraries(a.out ${LIBS})

#ctest
enable_testing()