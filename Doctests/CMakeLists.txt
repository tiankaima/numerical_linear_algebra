add_executable(Doctest_tests_run BaseTests/MatrixTest.cpp
        BaseTests/VectorTest.cpp
        GeneralTests/GaussMethodTest.cpp
        HomeworkTests/HW1Test.cpp
        HomeworkTests/HW2Test.cpp
        HomeworkTests/HW3Test.cpp
        HomeworkTests/HW4Test.cpp
        HomeworkTests/HW5Test.cpp
        HomeworkTests/HW6Test.cpp
        GeneralTests/PowerIterationTest.cpp)
target_link_libraries(Doctest_tests_run CustomMath_lib)