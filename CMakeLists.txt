cmake_minimum_required(VERSION 4.2)

project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test
	main.cpp
        file_menu.cpp
	program_menu.cpp)
