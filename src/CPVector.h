/**
 * @file CPVector.h
 * @brief This file is the main header of CPVector.
 * 
 * Inlcude this file in your source code in order to use CPVector with the configuration that was previously chosen.
 *
 * @author     Josem
 * @date       2023
 */
#ifndef CROSS_PLATFORM_VECTOR_H
#define CROSS_PLATFORM_VECTOR_H

	#include "CPVector_BuildSettings.h"

	
    /**
     * @namespace CPVector
	 * @brief This namespace contains the implementation of CPVector::vector class.
     *
     * The Vector namespace provides a set of classes and functions for working with a vector, a dynamic array that can resize itself when needed. It offers functionalities similar to the standard vector container in C++ STL.
     */
	namespace CPVector{}

	
	#if defined (CPVECTOR_SORTING_ENABLED)
		#include "Sorting/CPVector_Sorting.h"
	#endif

	#ifdef CPVECTOR_EXCEPTIONS_ENABLED
		#include "CPVector_Exceptions.h"
	#endif

	#include "CPVector_Template.h"

#endif//CROSS_PLATFORM_STRING_H