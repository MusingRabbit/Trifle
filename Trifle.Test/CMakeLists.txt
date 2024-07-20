set(ENGINE_NAME ${NAME}.Engine)
set(GAME_NAME ${NAME}.HelloVoxel)
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

add_executable(${TEST_NAME} ${TEST_SRC_FILES})

target_link_libraries(${TEST_NAME} glew)
target_link_libraries(${TEST_NAME} ${ENGINE_NAME})
target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES})
target_link_libraries(${TEST_NAME} ${LIBS})

# ctest
enable_testing()