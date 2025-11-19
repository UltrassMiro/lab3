project(DAL)

set(SOURCES
        EntityContext.cpp
        JSONProvider.cpp
        BinaryProvider.cpp
        CustomProvider.cpp
)

add_library(dal STATIC ${SOURCES})

target_include_directories(dal PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
