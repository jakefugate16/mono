cmake_minimum_required(VERSION 3.10)
project(upsidedown_triangle CXX C)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -O2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -mwindows")

file(COPY ${CMAKE_SOURCE_DIR}/src/shader.vert DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)
file(COPY ${CMAKE_SOURCE_DIR}/src/shader.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)


add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)
target_include_directories(glfw INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_executable(upsidedown_triangle
${CMAKE_SOURCE_DIR}/src/upsidedowntri.cpp
)

target_include_directories(upsidedown_triangle PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(upsidedown_triangle PRIVATE glad glfw opengl32 gdi32)
