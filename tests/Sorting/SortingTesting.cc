#include <gtest/gtest.h>
#include <CPVector.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the sortAscending() functionality of CPVector. 
//! The test begins by creating a vector with random values. Afterward, the vector 
//! is sorted in ascending order using the "sortAscending" method. 
//! Finally, a loop iterates through the sorted vector to ensure that each element 
//! is less than or equal to the next, using the "EXPECT_LE" assertion. 
//! This test verifies that the ascending sorting algorithm correctly orders the 
//! elements in the vector, confirming the integrity of the sorting functionality.
	
	TEST(SortingTesting, Ascending) {

		CPVector::vector<uint8_t> myVector(UINT8_MAX);
		ASSERT_EQ(myVector.size(), UINT8_MAX);

		for(uint8_t i = 0; i < myVector.size(); i++ )
		{
			myVector[i] = rand();
		}

		myVector.sortAscending();

		for(uint8_t i = 0; i < myVector.size()-1; i++ )
		{
			EXPECT_LE(myVector[i], myVector[i+1]);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
//! @test
//! This test case assesses the sortDescending() functionality of CPVector. 
//! The test begins by creating a vector with random values. Afterward, the vector 
//! is sorted in descending order using the "sortDescending" method. 
//! Finally, a loop iterates through the sorted vector to ensure that each element 
//! is greater than or equal to the next, using the "EXPECT_GE" assertion. 
//! This test verifies that the descending sorting algorithm correctly orders the 
//! elements in the vector, confirming the integrity of the sorting functionality.

	TEST(SortingTesting, Descending) {

		
		CPVector::vector<uint8_t> myVector(UINT8_MAX);
		ASSERT_EQ(myVector.size(), UINT8_MAX);

		for(uint8_t i = 0; i < myVector.size(); i++ )
		{
			myVector[i] = rand();
		}

		myVector.sortDescending();

		for(uint8_t i = 0; i < myVector.size()-1; i++ )
		{
			EXPECT_GE(myVector[i], myVector[i+1]);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
//

	namespace {
		struct TestingStruct
		{
			public:

				uint8_t A;
				uint8_t B;
		};

	    int8_t TestingStruct_A_Ascending(const TestingStruct& Element, const TestingStruct& Pivot)
	    {
	        if(Element.A==Pivot.A){return CPVector::Sorting::Equal;}
	        else if(Element.A<Pivot.A){return CPVector::Sorting::Swap;}
	        else{return CPVector::Sorting::Ignore;}
	    }

	    int8_t TestingStruct_B_Ascending(const TestingStruct& Element, const TestingStruct& Pivot)
	    {
	        if(Element.B==Pivot.B){return CPVector::Sorting::Equal;}
	        else if(Element.B<Pivot.B){return CPVector::Sorting::Swap;}
	        else{return CPVector::Sorting::Ignore;}
	    }
	}

	//////////////////////////////////////////////////////////////////////////////
	//! @test
	//! This unit test, named "SortingTesting," evaluates the sorting functionality of 
	//! a CPVector::vector containing elements of a user-defined structure.
	//! The test commences by creating a vector of "TestingStruct" instances with a size 
	//! equal to UINT8_MAX and verifies that the vector size matches this value. 
	//! It proceeds to populate each element of the vector with random values 
	//! for members "A" and "B." \n\n
	//! The test configures a CPVector::Sorting::SortingArray named "SortConfig" with two sorting functions, 
	//! "TestingStruct_A_Ascending" and "TestingStruct_B_Ascending," which determine how 
	//! the elements should be sorted based on the values of their "A" and "B" members. 
	//! The custom sorting algorithm is applied to the vector using "myVector.sort(SortConfig)."\n\n
	//! The final part of the test asserts that the vector is sorted correctly in ascending 
	//! order based on the values of "A" and, if "A" values are equal, based on the values 
	//! of "B." This comprehensive test ensures the integrity of the sorting algorithm for 
	//! custom structures and multi-level sorting within the CPVector class.
	//! @{

		TEST(SortingTesting, SortingList) {

			CPVector::vector<TestingStruct> myVector(UINT8_MAX);
			ASSERT_EQ(myVector.size(), UINT8_MAX);

			for(uint8_t i = 0; i < myVector.size(); i++ )
			{
				myVector[i].A = rand();
				myVector[i].B = rand();
			}


			CPVector::Sorting::SortingArray<TestingStruct> SortConfig;
			SortConfig.push_back(TestingStruct_A_Ascending);
			SortConfig.push_back(TestingStruct_B_Ascending);

			myVector.sort(SortConfig);

			for(uint8_t i = 0; i < myVector.size()-1; i++ )
			{
				EXPECT_LE(myVector[i].A, myVector[i+1].A);

				if(myVector[i].A == myVector[i+1].A)
				{
					EXPECT_LE(myVector[i].B, myVector[i+1].B);
				}
			}
		}
	//! @}
	//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////
