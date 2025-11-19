project(PL)

add_executable(app
        main.cpp
)

target_include_directories(app PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ../BLL
        ../DAL
)

target_link_libraries(app PRIVATE bll dal)
