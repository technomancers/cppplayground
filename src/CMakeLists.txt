configure_file(todoConfig.h.in ${CMAKE_SOURCE_DIR}/src/todoConfig.h)

add_executable(todo main.cpp)