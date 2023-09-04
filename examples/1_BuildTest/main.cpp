#include <iostream>
#include <CPVector.h>

int main()
{
    std::cout<<"This project uses CPVector version: "<<CPVECTOR_VERSION<<std::endl;

    #if defined(CPVECTOR_SORTING_ENABLED)
    	std::cout<<"CPVector::Sorting Enabled."<<std::endl;
    #endif



        CPVector::vector<CPVector::vector<uint8_t>> myVector(10, CPVector::vector<uint8_t>(2) );

        auto myVector2 = CPVector::move(myVector);


        myVector.push_back(CPVector::move(CPVector::vector<uint8_t>(1)));
        myVector.emplace(CPVector::move(CPVector::vector<uint8_t>(5)), 0);


        std::cout << myVector.size() << ", " << myVector2.size() << std::endl;
        std::cout << myVector.capacity() << ", " << myVector2.capacity() << std::endl;

        std::cout << (unsigned int)myVector[0].size() << std::endl;
        std::cout << (unsigned int)myVector[1].size() << std::endl;

    return 0;
}