set (ENGINE_NAME ${NAME}.Engine)

message("ENGINE_NAME = ${ENGINE_NAME}")
message("CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

include_directories(${PROJECT_SOURCE_DIR}/includes)

set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/${ENGINE_NAME})
set(ENGINE_SOURCE_DIR ${ENGINE_DIR}/src)

message("LIBS = ${LIBS}")

file(GLOB_RECURSE SOURCE_FILES
${ENGINE_SOURCE_DIR}/*.c
${ENGINE_SOURCE_DIR}/*.cpp
${ENGINE_SOURCE_DIR}/*.h
${ENGINE_SOURCE_DIR}/*.hpp
)

#message("SOURCE_FILES = ${SOURCE_FILES}")

add_library(${ENGINE_NAME} STATIC ${SOURCE_FILES})
target_include_directories(${ENGINE_NAME} PUBLIC ${ENGINE_SOURCE_DIR})
target_include_directories(${ENGINE_NAME} PRIVATE ${OPENGL_INCLUDE_DIR})
#target_link_libraries(${ENGINE_NAME} PRIVATE ${LIBS})