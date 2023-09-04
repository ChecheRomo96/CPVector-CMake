#include <gtest/gtest.h>
#include <CPVector.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
// reserve

	TEST(BasicFunctionalityTesting, reserve) {

		CPVector::vector<uint8_t> myVector;
		ASSERT_EQ(myVector.size(),0);

		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			myVector.resize(i);
			ASSERT_EQ(myVector.size(),i);
			ASSERT_GE(myVector.capacity(),i);
		}

		myVector.clear();
		ASSERT_EQ(myVector.size(),0);
		ASSERT_EQ(myVector.capacity(),0);

		myVector.reserve(UINT8_MAX);
		ASSERT_EQ(myVector.size(),0);
		ASSERT_GE(myVector.capacity(),UINT8_MAX);

		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			myVector.resize(i);
			ASSERT_EQ(myVector.size(),i);
			ASSERT_GE(myVector.capacity(),UINT8_MAX);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// resize

	TEST(BasicFunctionalityTesting, resize) {

		CPVector::vector<uint8_t> myVector;
		ASSERT_EQ(myVector.size(),0);

		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			myVector.resize(i);
			ASSERT_EQ(myVector.size(),i);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// resize_initialization

	TEST(BasicFunctionalityTesting, resize_initialization) {

		CPVector::vector<uint8_t> myVector;

		for(uint8_t i = 1; i < UINT8_MAX; i++ )
		{
			bool MemoryAllocationStatus = myVector.resize(i);
			ASSERT_EQ(MemoryAllocationStatus,1);
			EXPECT_EQ(myVector.size(),i);
			EXPECT_EQ(myVector[i-1],(uint8_t)0u);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// clear

	TEST(BasicFunctionalityTesting, clear) {

		CPVector::vector<uint8_t> myVector;
		ASSERT_EQ(myVector.size(),0);

		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			myVector.resize(i);
			ASSERT_EQ(myVector.size(),i);
			myVector.clear();
			EXPECT_EQ(myVector.size(),0);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// copy

	TEST(BasicFunctionalityTesting, copy) {

		uint8_t Data[UINT8_MAX] = {};
		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			Data[i] = i;
		}

		CPVector::vector<uint8_t> myVector;

		myVector.copy(Data + 10, 10, 1);
		ASSERT_EQ(myVector.size(), 10);
		
		for(uint8_t i = 0; i < 10; i++ )
		{
			EXPECT_EQ(myVector[i],10+i);
		}

	}
//
//////////////////////////////////////////////////////////////////////////////////
// push_back

	TEST(BasicFunctionalityTesting, push_back) {

		uint8_t Data[UINT8_MAX] = {};
		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			Data[i] = i;
		}

		CPVector::vector<uint8_t> myVector;

		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			myVector.push_back(Data[i]);
			ASSERT_EQ(myVector.size(),i+1);
			EXPECT_EQ(myVector[i],i);
		}

	}
//
//////////////////////////////////////////////////////////////////////////////////
// pop

	TEST(BasicFunctionalityTesting, pop) {

		uint8_t Data[UINT8_MAX] = {};
		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			Data[i] = i;
		}

		CPVector::vector<uint8_t> myVector;
		myVector.copy(Data,UINT8_MAX,1);

		ASSERT_EQ(myVector.size(),UINT8_MAX);

		uint8_t counter = 0;
		while(myVector.size() > 0)
		{
			EXPECT_EQ(myVector[0],counter++);
			myVector.pop(0);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// pop_first

	TEST(BasicFunctionalityTesting, pop_first) {

		uint8_t Data[UINT8_MAX] = {};
		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			Data[i] = i;
		}

		CPVector::vector<uint8_t> myVector;
		myVector.copy(Data,UINT8_MAX,1);

		ASSERT_EQ(myVector.size(),UINT8_MAX);

		uint8_t counter = 0;
		while(myVector.size() > 0)
		{
			EXPECT_EQ(myVector[0],counter++);
			myVector.pop_first();
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// pop_back

	TEST(BasicFunctionalityTesting, pop_back) {

		uint8_t Data[UINT8_MAX] = {};
		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			Data[i] = i;
		}

		CPVector::vector<uint8_t> myVector;
		myVector.copy(Data,UINT8_MAX,1);

		ASSERT_EQ(myVector.size(),UINT8_MAX);

		uint8_t counter = UINT8_MAX-1;
		while(myVector.size() > 0)
		{
			EXPECT_EQ(myVector[myVector.size()-1],counter--);
			myVector.pop_back();
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// emplace

	TEST(BasicFunctionalityTesting, emplace) {

		CPVector::vector<uint8_t> myVector;

		EXPECT_EQ(myVector.size(),0);

		uint8_t counter = 0;
		while(myVector.size() > 0)
		{
			myVector.emplace(counter,0);
			EXPECT_EQ(myVector[0],counter++);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// swap

	TEST(BasicFunctionalityTesting, swap) {

		CPVector::vector<uint8_t> myVector;
		EXPECT_EQ(myVector.size(),0);

		uint8_t counter = 0;
		for(uint8_t i = 0; i < 10; i++)
		{
			myVector.push_back(i);
		}

		for(uint8_t i = 0; i < 5; i++)
		{
			myVector.swap(i,9-i);
		}

		for(uint8_t i = 0; i < 10; i ++)
		{
			EXPECT_EQ(myVector[i],9-i);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// erase

	TEST(BasicFunctionalityTesting, erase) {

		uint8_t Data[UINT8_MAX] = {};
		for(uint8_t i = 0; i < UINT8_MAX; i++ )
		{
			Data[i] = i;
		}

		CPVector::vector<uint8_t> myVector;
		myVector.copy(Data,UINT8_MAX,1);

		uint8_t counter = 0;
		
		while(myVector.size() > 0)
		{
			EXPECT_EQ(myVector[0],counter++);
			myVector.erase(0);
		}
	}
//
/////////////////////////////////////////////////////////////////////////////////