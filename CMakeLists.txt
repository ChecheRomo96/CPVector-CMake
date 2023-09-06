######################################################################################################
# Setting up the project

	##################################################################################################
	# C Make Minimum Version
		
		cmake_minimum_required(VERSION 3.14)
	#
	##################################################################################################
	# Project Name Version and Languaje, print and add preprocessor flag
		
		project(CPVector VERSION 1.0.0 LANGUAGES CXX)
		message(STATUS "Building ${PROJECT_NAME} Version = ${PROJECT_VERSION}...")

		string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
	#
	##################################################################################################
	# Set up C++ Version

		set(CMAKE_CXX_STANDARD 17) 
		set(CMAKE_CXX_STANDARD_REQUIRED ON)
	#
	##################################################################################################
#
######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( ${PROJECT_NAME_UPPER}_ROOT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Compile Configuration
	
	set(CPVECTOR_ALLOCATION_METHOD "dummy" CACHE STRING "CPVector allocation method")
	set_property(CACHE CPVECTOR_ALLOCATION_METHOD PROPERTY STRINGS  "std::vector" "CPP" "C")

	#set(CPVECTOR_USE_STD_VECTOR_ALLOCATION FALSE CACHE BOOL "CPVector::vector using std::vector")
	#set(CPVECTOR_USE_C_ALLOCATION FALSE CACHE BOOL "CPVector::vector using C allocators (malloc, calloc, free) ")
	#set(CPVECTOR_USE_CPP_ALLOCATION FALSE CACHE BOOL "CPVector::vector using C++ allocators (new, new[], delete, delete[]).")

	set(CPVECTOR_EXCEPTIONS FALSE CACHE BOOL "Exception functionality toggle, TRUE = Enabled.")

	set(CPVECTOR_SORTING FALSE CACHE BOOL "Compile CPVector::Sorting")

	set(CPVECTOR_EXAMPLES FALSE CACHE BOOL "Build Examples")
	set(CPVECTOR_TESTING FALSE CACHE BOOL "Testing Enabled")	
#
######################################################################################################
# Append Source

	add_subdirectory(src)
	
	target_compile_definitions(CPVector INTERFACE ${PROJECT_NAME_UPPER}_VERSION="${PROJECT_VERSION}" )

#
######################################################################################################
# Append Examples

	if( ${CPVECTOR_EXAMPLES} )
		message("Building ${CMAKE_PROJECT_NAME} Examples...")
		add_subdirectory(examples)
	endif()
#
######################################################################################################
# Append Tests

	if( ${CPVECTOR_TESTING} )
		message("Building ${CMAKE_PROJECT_NAME} Tests...")

		cmake_policy(SET CMP0135 NEW)

		include(FetchContent)

		FetchContent_Declare(
		  googletest
		  URL https://github.com/google/googletest/archive/f8d7d77c06936315286eb55f8de22cd23c188571.zip
		)
		# For Windows: Prevent overriding the parent project's compiler/linker settings
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
		FetchContent_MakeAvailable(googletest)

		enable_testing()
		include(GoogleTest)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${${PROJECT_NAME_UPPER}_ROOT_DIRECTORY}/bin")
		add_subdirectory(tests)
	endif()
#
######################################################################################################
