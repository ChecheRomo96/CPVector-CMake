add_executable( CPVector_ExceptionTesting ExceptionTesting.cc ) 
target_link_libraries( CPVector_ExceptionTesting PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_ExceptionTesting)