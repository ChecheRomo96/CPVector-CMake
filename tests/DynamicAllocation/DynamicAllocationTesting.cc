#include <gtest/gtest.h>
#include <CPVector.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////
// dynamicAllocation1

	TEST(DynamicAllocationTesting, VectorPointerToObject) {

        #if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION) || defined(CPVECTOR_USING_CPP_ALLOCATION)
			CPVector::vector<uint8_t>* myVectorptr = nullptr;

			EXPECT_EQ((void*)myVectorptr,nullptr);
			
			myVectorptr = new CPVector::vector<uint8_t>(12);

			ASSERT_NE(myVectorptr,nullptr);

			EXPECT_EQ(myVectorptr->size(),12);

			delete(myVectorptr);
		#elif (CPVECTOR_USING_C_ALLOCATION)

			CPVector::vector<uint8_t>* myVectorptr = NULL;

			EXPECT_EQ((void*)myVectorptr,NULL);
			
			myVectorptr = (CPVector::vector<uint8_t>*)malloc(sizeof(CPVector::vector<uint8_t>) * 12);

			ASSERT_NE(myVectorptr,NULL);

			EXPECT_EQ(myVectorptr->size(),12);

			delete(myVectorptr);

		#endif
	}
//
//////////////////////////////////////////////////////////////////////////////////
// dynamicAllocation2

    #if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION) || defined(CPVECTOR_USING_CPP)
		TEST(DynamicAllocationTesting, VectorPointerToArray) {

			CPVector::vector<uint8_t>* myVectorptr = nullptr;

			EXPECT_EQ((void*)myVectorptr,nullptr);
			
			myVectorptr = new CPVector::vector<uint8_t>[8];

			ASSERT_NE(myVectorptr,nullptr);

			for(uint8_t i = 0; i < 8; i++){
				myVectorptr[i] = CPVector::vector<uint8_t>(8);
				ASSERT_EQ(myVectorptr[i].size(), 8);

			    for(uint8_t j = 0; j < 8; j++){    
					myVectorptr[i][j] = (8*i) + j;
			    }
			}
			
			for(uint8_t i = 0; i < 8; i++){
			    for(uint8_t j = 0; j < 8; j++){
			        EXPECT_EQ(myVectorptr[i][j], (8*i) + j);
			    }
			}

			delete[] myVectorptr;
		}
	#endif
//
//////////////////////////////////////////////////////////////////////////////////
// dynamicAllocation3

	TEST(DynamicAllocationTesting, VectorOfVectors) {
		CPVector::vector<CPVector::vector<uint8_t>> myVector(8);

		ASSERT_EQ(myVector.size(),8);

		for(uint8_t i = 0; i < myVector.size(); i++)
		{
			ASSERT_EQ(myVector[i].size(),0);

			myVector[i].resize(8);
			ASSERT_EQ(myVector[i].size(),8);

			for(uint8_t j = 0; j < myVector[i].size(); j++)
			{
				myVector[i][j] = (8*i) + j;
				EXPECT_EQ(myVector[i][j], (8*i) + j);
			}
		}

		for(uint8_t i = 0; i < myVector.size(); i++)
		{
			for(uint8_t j = 0; j < myVector[i].size(); j++)
			{
				myVector[i][j] = (8*i) + j;
				EXPECT_EQ(myVector[i][j], (8*i) + j);
			}
			myVector[i].clear();
		}

		myVector.clear();
	}
//
//////////////////////////////////////////////////////////////////////////////////