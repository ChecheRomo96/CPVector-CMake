add_executable( CPVector_BasicFunctionality BasicFunctionalityTesting.cc ) 
target_link_libraries( CPVector_BasicFunctionality PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_BasicFunctionality)

add_executable( CPVector_Constructors ConstructorTesting.cc ) 
target_link_libraries( CPVector_Constructors PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_Constructors)

add_executable( CPVector_DynamicAllocation DynamicAllocationTesting.cc ) 
target_link_libraries( CPVector_DynamicAllocation PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_DynamicAllocation)

add_executable( CPVector_Operators OperatorTesting.cc ) 
target_link_libraries( CPVector_Operators PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_Operators)