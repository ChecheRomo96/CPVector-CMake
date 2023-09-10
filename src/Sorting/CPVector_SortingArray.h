#ifndef CROSS_PLATFORM_VECTOR_SORTING_ARRAY_H
#define CROSS_PLATFORM_VECTOR_SORTING_ARRAY_H
	
    #include "CPVector_BuildSettings.h"
	#include "CPVector_Sorting.h"

	namespace CPVector
	{
        template <class T>
        class vector;
	}

	namespace CPVector::Sorting
	{
		////////////////////////////////////////////////////////////////////////
		// SortingArray Class

			/**
			 * @brief      Dynamic array of CPVector::Sorting::Callback, used to sort CPVector::vector with multiple condiditions.
			 * 
			 * Relevance in the sorting process is defined by the index of each compare function. First has the most priority.\n
			 * In order to append new callbacks use push_back(), or emplace(), to remove an element use erase(). 
			 * @tparam     T	Class to be used as parameters for the Callbacks.
			 */
			template <class T>
	        class SortingArray : public CPVector::vector<Callback<T>>{

	        private:
	        	using CPVector::vector<Callback<T>>::sortAscending;
	        	using CPVector::vector<Callback<T>>::sortDescending;
	        	using CPVector::vector<Callback<T>>::sort;

            public:

                SortingArray(){

                }
            
                ~SortingArray(){

                }

                Result compare(const T& a, const T& b) const
                {
             		if(CPVector::vector<Callback<T>>::size() == 0){return CPVector::Sorting::Equal;}
                    
                    uint8_t index = 0;
                    Result result = CPVector::Sorting::Equal;
                    
                    while(result == CPVector::Sorting::Equal)
                    {
                        result = (*this)[index](a,b);
                        index++;
                        if(index == CPVector::vector<Callback<T>>::size()){return result;}
                    }

                    return result;
                }
	        };
	    //
        ////////////////////////////////////////////////////////////////////////
	}

#endif//CROSS_PLATFORM_VECTOR_SORTING_ARRAY_H