cmake_minimum_required(VERSION 3.10)
project(crateglm LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-Wall -O2)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -mwindows")

#copy resource files to build here
file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/res)
file(COPY ${CMAKE_SOURCE_DIR}/res/shaders/shader.vert DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/shaders)
file(COPY ${CMAKE_SOURCE_DIR}/res/shaders/shader.frag DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res/shaders)
file(COPY ${CMAKE_SOURCE_DIR}/res/textures DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/res)

#add libraries
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)
target_include_directories(glfw INTERFACE ${CMAKE_SOURCE_DIR}/include)

find_package(glm CONFIG REQUIRED)

add_executable( ${CMAKE_PROJECT_NAME}
	${CMAKE_SOURCE_DIR}/src/crateglm.cpp
)

#set include directories
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${glm_INCLUDE_DIRS})

#link libs
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE glad glfw glm::glm opengl32 gdi32)
