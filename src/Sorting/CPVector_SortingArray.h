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

			template <class T>
	        class SortingArray
	        {
	            ////////////////////////////////////////////////////////////////
	            // Compare Function Vector

	            	CPVector::vector<Result(*)(const T& a, const T& b)> buffer;
	            //
	            ////////////////////////////////////////////////////////////////

	            public:

	        	////////////////////////////////////////////////////////////////
	        	// Constructor and Destructor

	                SortingArray()
	                {

	                }
	            
	                ~SortingArray()
	                {

	                }
	        	//
	        	////////////////////////////////////////////////////////////////
	        	// API

                    void copy(const Sorting::Callback<T>* Callbacks, unsigned int len, bool Resize = 0)
	                {
	                	buffer.copy(Callbacks,len,Resize);
	                }

                    void copy(const CPVector::vector<Sorting::Callback<T>>& vector, unsigned int len, bool Resize = 0)
	                {
	                	auto min = (vector.size()<len)?vector.size():len;
	                	buffer.copy(vector[0],min,Resize);
	                }

	                void push_back(Result(*Fn)(const T& a, const T& b))
	                {
	                    if(Fn != NULL)
	                    {
	                        buffer.push_back(Fn);
	                    }
	                }

	                void swap(unsigned int a, unsigned int b)
	                {
	                	buffer.swap(a,b);
	                }

	                void emplace(unsigned int a, unsigned int b)
	                {
	                	buffer.swap(a,b);
	                }
	            
	                void erase(unsigned int n)
	                {
	                    buffer.erase(n);
	                }

                    void erase(unsigned int first, unsigned int last)
                    {
	                    buffer.erase(first, last);
                    }
	            
	                void erase(Sorting::Callback<T> Fn)
	                {
	                	for(uint8_t i = 0; i < buffer.size(); i++)
	                	{
	                		if(buffer[i] == Fn)
	                		{
	                			buffer.erase(i--);
	                		}
	                	}
	                }

	                Result compare(const T& a, const T& b) const
	                {
	             		if(buffer.size() == 0){return CPVector::Sorting::Equal;}
	                    
	                    uint8_t index = 0;
	                    Result result = CPVector::Sorting::Equal;
	                    
	                    while(result == CPVector::Sorting::Equal)
	                    {
	                        result = buffer[index](a,b);
	                        index++;
	                        if(index == buffer.size()){return result;}
	                    }

	                    return result;
	                }
	        	//
	        	////////////////////////////////////////////////////////////////
	        };
	    //
        ////////////////////////////////////////////////////////////////////////
	}

#endif//CROSS_PLATFORM_VECTOR_SORTING_ARRAY_H