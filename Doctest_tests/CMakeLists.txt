add_executable(Doctest_tests_run MatrixTest.cpp
        ArrayTest.cpp)
target_link_libraries(Doctest_tests_run CustomMath_lib)