set(ENGINE_NAME ${NAME}.Engine)
set(GAME_NAME ${NAME}.Game)
set(TEST_NAME ${NAME}.Test)

set(TEST_DIR, "$${PROJECT_SOURCE_DIR}/{NAME}/")

set(LIBS ${LIBS} gtest)
message(STATUS "LIBS = ${LIBS}")

add_executable(a.out ${TEST_DIR}Main.cpp VoxelGridHelper_Tests.h)

target_link_libraries(a.out ${GTEST_LIBRARIES})

#ctest
enable_testing()
add_test(EmptyTest a.out)

target_link_libraries(a.out ${ENGINE_NAME})