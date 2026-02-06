cmake_minimum_required(VERSION 3.10)
project(texturecrate LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -O2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -mwindows")

#copy resource files to build here
file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#add libraries
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)
target_include_directories(glfw INTERFACE ${CMAKE_SOURCE_DIR}/include)


add_executable( ${CMAKE_PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/src/crate.cpp
)

#set include directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)

#link libs
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw opengl32 gdi32)
