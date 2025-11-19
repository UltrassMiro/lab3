cmake_minimum_required(VERSION 3.10)
project(StudentsProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(DAL)
add_subdirectory(BLL)
add_subdirectory(PL)
