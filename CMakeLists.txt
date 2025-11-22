cmake_minimum_required(VERSION 3.16)

project(StudentsSerialization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES
        "${CMAKE_SOURCE_DIR}/main.cpp"
        "${CMAKE_SOURCE_DIR}/BLL/*.cpp"
        "${CMAKE_SOURCE_DIR}/DAL/*.cpp"
        "${CMAKE_SOURCE_DIR}/PL/*.cpp"
)
enable_testing()
add_subdirectory(tests)

add_executable(students_app ${SRC_FILES}
        DAL/Librarian.h
        DAL/SoftwareDeveloper.h
#[[        tests/Student_tests.cpp
        tests/StudentService_tests.cpp]])



target_include_directories(students_app PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/BLL
        ${CMAKE_SOURCE_DIR}/DAL
        ${CMAKE_SOURCE_DIR}/PL
        ${CMAKE_SOURCE_DIR}/external/googletest
)
