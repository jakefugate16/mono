cmake_minimum_required(VERSION 3.20)
project(dialog LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -O2)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#find Qt
set(CMAKE_PREFIX_PATH /msys64/ucrt64/qt5-static)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(${CMAKE_PROJECT_NAME}
	main.cpp
	src/window.cpp
)

#set library directory
#target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE -static-libstdc++ -static-libgcc -pthread)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
	Qt5::Core 
	Qt5::Widgets
	Qt5::Gui
	z
	zstd
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
	WIN32_EXECUTABLE ON
)
