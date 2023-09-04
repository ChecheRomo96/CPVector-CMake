add_executable( CPVector_Constructors ConstructorTesting.cc ) 
target_link_libraries( CPVector_Constructors PUBLIC CPVector PUBLIC GTest::gtest_main )
gtest_discover_tests(CPVector_Constructors)