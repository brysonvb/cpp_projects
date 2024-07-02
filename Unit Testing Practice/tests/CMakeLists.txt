enable_testing()
find_package(GTest REQUIRED)

include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_my_functions test_my_functions.cpp)

target_link_libraries(test_my_functions ${GTEST_LIBRARIES} pthread my_functions)

add_test(NAME test_my_functions COMMAND test_my_functions)
