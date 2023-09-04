#include <gtest/gtest.h>
#include <CPVector.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
// Ascending

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
// Descending

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
// SortingList
// 
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
//
//////////////////////////////////////////////////////////////////////////////////
