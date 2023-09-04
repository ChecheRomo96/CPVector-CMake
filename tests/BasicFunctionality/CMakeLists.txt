add_executable( CPVector_BasicFunctionality BasicFunctionalityTesting.cc ) 
target_link_libraries( CPVector_BasicFunctionality PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_BasicFunctionality)