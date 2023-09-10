#include <iostream>
#include <CPVector.h>

int main()
{
    std::cout<<"This project uses CPVector version: "<<CPVECTOR_VERSION<<std::endl;

    #if defined(CPVECTOR_SORTING_ENABLED)
    	std::cout<<"CPVector::Sorting Enabled."<<std::endl;
    #endif

    #if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
        std::cout<<"CPVector::vector will act as a std::vector wrapper."<<std::endl;
    #endif

    #if defined(CPVECTOR_USING_CPP_ALLOCATION)
        std::cout<<"CPVector::vector will handle allocations with C++ allocators new, new[], delete, and delte[]."<<std::endl;
    #endif

    #if defined(CPVECTOR_USING_C_ALLOCATION)
        std::cout<<"CPVector::vector will handle allocations with C allocators malloc, calloc, realloc, free."<<std::endl;
    #endif

    return 0;
}