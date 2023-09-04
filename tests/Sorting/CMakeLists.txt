add_executable( CPVector_Sorting SortingTesting.cc ) 
target_link_libraries( CPVector_Sorting PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_Sorting)