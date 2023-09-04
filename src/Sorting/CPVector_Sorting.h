#ifndef CROSS_PLATFORM_VECTOR_SORTING_H
#define CROSS_PLATFORM_VECTOR_SORTING_H


    #include "CPVector_BuildSettings.h"
    
	/**
     *  @defgroup Sorting Sorting
     *  @brief Functionality related to sorting vectors.
     */


    /**
     * @ingroup Sorting
     * @brief Namespace containing the sorting functionality of CPVector::vector
     *
     * Any Result that is not Swap, Equal, or Ignore, will have no efect on the sorting functionality of the vector. 
     */
	namespace CPVector::Sorting
	{
      	////////////////////////////////////////////////////////////////////////
      	// type used as return type for comparing functions

            /**
             * @ingroup Sorting
             * @brief return type for comparing functions
             *
             * Any Result that is not Swap, Equal, or Ignore, will have no efect on the sorting functionality of the vector. 
             */
          	typedef int8_t Result;

            /**
             * @ingroup Sorting
             * @brief Template callback type
             *
             * Used in CPVector::vector<T> in order to reference a Sorting::Callback. A Sorting::Callback stores a pointer to a function that follows the required convention.\n\n
             * The sorting function definition must recive two contstant references to a template type object, and must return a CPVector::Sorting::Result containing CPVector::Sorting::Equal, CPVector::Sorting::Swap, or CPVector::Sorting::Ignore.\n\n
             * Check CPVector::Sorting::Ascending and CPVector::Sorting::Descending as a reference.
             */
          	template<class T>
          	using Callback = Result(*)(const T&, const T&);
        //
      	////////////////////////////////////////////////////////////////////////
      	// Definitions

            /**
             * @ingroup Sorting
             * @brief Used to indicate that the objects being compared should be swapped.
             *
             * An object must be swapped if the element being compared should go before the pivot. For example, the function CPVector::Sort::Ascending() returns swap whenever Element < Pivot, hence Element goes before Pivot.
             */
      		static constexpr Result Swap = 1;

            /**
             * @ingroup Sorting
             * @brief Used to indicate that the objects being compared are equal under a specific criteria.
             *
             * If a comparison yields equal and there are no more criterions available, the elements are not swapped.
             */
      		static constexpr Result Equal = 0;

            /**
             * @ingroup Sorting
             * @brief Used to indicate that the objects being compared should not be swapped.
             *
             * An object must be swapped if the element being compared should go after the pivot. For example, the function CPVector::Sort::Ascending() returns ignore whenever Element > Pivot, hence Element goes after Pivot.
             */
      		static constexpr Result Ignore = -1;
        //
        ////////////////////////////////////////////////////////////////////////
        // Comparing functions templates

            /**
             * @ingroup Sorting
             * @brief Template function that enables sorting elements in an ascending manner.
             *
             * Works with any class that has operators > , < and ==.
             */
	        template <class T>
	        Result Ascending(const T& Element, const T& Pivot)
	        {
	            if(Element==Pivot){return Sorting::Equal;}
	            else if(Element<Pivot){return Sorting::Swap;}
	            else{return Sorting::Ignore;}
	        }
	        
            /**
             * @ingroup Sorting
             * @brief Template function that enables sorting elements in an descending manner.
             *
             * Works with any class that has operators > , < and == available.
             */
	        template <class T>
	        Result Descending(const T& Element, const T& Pivot)
	        {
	            if(Element==Pivot){return Sorting::Equal;}
	            else if(Element>Pivot){return Sorting::Swap;}
	            else{return Sorting::Ignore;}
	        }
        //
        ////////////////////////////////////////////////////////////////////////
	}

	#include "CPVector_SortingArray.h"

#endif//CROSS_PLATFORM_VECTOR_SORTING_H