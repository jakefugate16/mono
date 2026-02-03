cmake_minimum_required(VERSION 3.10)
project(interpolated_triangle CXX C)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -O2)

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libglfw3.a")
target_include_directories(glfw INTERFACE "${CMAKE_SOURCE_DIR}/include")

add_executable(
 ${PROJECT_NAME}
 interpolated_triangle.cpp
 )

target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw opengl32 gdi32)
