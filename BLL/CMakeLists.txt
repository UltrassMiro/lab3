project(BLL)

set(SOURCES
        StudentService.cpp
)

add_library(bll STATIC ${SOURCES})

target_include_directories(bll PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(bll PUBLIC dal)
