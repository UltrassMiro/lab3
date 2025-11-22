cmake_minimum_required(VERSION 3.10)

project(StudentsSerialization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
        "${CMAKE_SOURCE_DIR}/main.cpp"
        "${CMAKE_SOURCE_DIR}/BLL/*.cpp"
        "${CMAKE_SOURCE_DIR}/DAL/*.cpp"
        "${CMAKE_SOURCE_DIR}/PL/*.cpp"
)

add_executable(students_app ${SRC_FILES})

target_include_directories(students_app PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/BLL
        ${CMAKE_SOURCE_DIR}/DAL
        ${CMAKE_SOURCE_DIR}/PL
)
