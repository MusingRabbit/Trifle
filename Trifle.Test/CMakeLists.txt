set (NAME ${NAME}.Test)
set(TEST_DIR, "$${PROJECT_SOURCE_DIR}/{NAME}/")

set(LIBS LIBS ${GTEST_LIBRARIES})

add_executable(${NAME} ${TEST_DIR}Main.cpp)

#ctest
enable_testing()
add_test(Empty_Test ${NAME})


