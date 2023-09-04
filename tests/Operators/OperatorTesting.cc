#include <gtest/gtest.h>
#include <CPVector.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
// Assignment Operator

	TEST(OperatorTesting, Assignment) {

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
// Subscript Array Operator

	TEST(OperatorTesting, SubscriptArray) {

		CPVector::vector<uint8_t> myVector(5);
		ASSERT_EQ(myVector.size(),5);

		for(uint8_t i = 0; i < myVector.size(); i++ )
		{
			myVector[i] = i;
			ASSERT_EQ(myVector[i],i);
		}
	}
//
//////////////////////////////////////////////////////////////////////////////////
// Comparison Operators

	TEST(OperatorTesting, Comparison) {

		CPVector::vector<uint8_t> myVector1;
		CPVector::vector<uint8_t> myVector2(5);

		ASSERT_EQ(myVector1.size(),0);
		ASSERT_EQ(myVector2.size(),5);
		EXPECT_EQ(myVector1!=myVector2,1);
		EXPECT_EQ(myVector1==myVector2,0);

		myVector1.resize(5);
		myVector2.resize(5);

		ASSERT_EQ(myVector1.size(),5);
		ASSERT_EQ(myVector2.size(),5);
		EXPECT_EQ(myVector1!=myVector2,0);
		EXPECT_EQ(myVector1==myVector2,1);

		myVector1[0] = 1;
		myVector1[1] = 2;

		myVector2[0] = 2;
		myVector2[1] = 2;

		ASSERT_EQ(myVector1.size(),5);
		ASSERT_EQ(myVector2.size(),5);
		EXPECT_EQ(myVector1!=myVector2,1);
		EXPECT_EQ(myVector1==myVector2,0);

		myVector1[0] = 3;
		myVector1[1] = 3;

		myVector2[0] = 3;
		myVector2[1] = 3;

		ASSERT_EQ(myVector1.size(),5);
		ASSERT_EQ(myVector2.size(),5);
		EXPECT_EQ(myVector1!=myVector2,0);
		EXPECT_EQ(myVector1==myVector2,1);
	}
//
//////////////////////////////////////////////////////////////////////////////////