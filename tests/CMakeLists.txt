cmake_minimum_required(VERSION 3.16)
project(StudentTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

# Підключаємо локальний googletest
add_subdirectory(
        ${CMAKE_SOURCE_DIR}/external/googletest
        ${CMAKE_BINARY_DIR}/external/googletest
)


# Твоя бібліотека
add_library(student_lib
        ../DAL/Student.h
#[[        ../DAL/Student.cpp]]
        ../BLL/StudentService.h
        ../BLL/StudentService.cpp
        ../DAL/EntityContext.h
        ../DAL/EntityContext.cpp
        ../DAL/DataProvider.h
        ../DAL/JSONProvider.h
        ../DAL/JSONProvider.cpp
        ../DAL/BinaryProvider.h
        ../DAL/CustomProvider.h
)

target_include_directories(student_lib PUBLIC ${CMAKE_SOURCE_DIR}/..)

# Тести
add_executable(student_tests
        Student_tests.cpp
        StudentService_tests.cpp
)

target_link_libraries(student_tests
        student_lib
        gtest
        gtest_main
        gmock
        gmock_main
)

include(GoogleTest)
gtest_discover_tests(student_tests)
