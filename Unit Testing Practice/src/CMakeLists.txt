add_library(my_functions my_functions.cpp)
add_executable(main main.cpp)
target_link_libraries(main my_functions)
