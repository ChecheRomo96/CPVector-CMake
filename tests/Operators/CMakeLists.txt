add_executable( CPVector_Operators OperatorTesting.cc ) 
target_link_libraries( CPVector_Operators PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_Operators)