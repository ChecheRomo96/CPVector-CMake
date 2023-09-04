add_executable( CPVector_DynamicAllocation DynamicAllocationTesting.cc ) 
target_link_libraries( CPVector_DynamicAllocation PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_DynamicAllocation)