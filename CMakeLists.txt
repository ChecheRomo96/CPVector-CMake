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

	set(CPVECTOR_BUILD_EXAMPLES FALSE CACHE BOOL "Build CPVector Examples")
	set(CPVECTOR_TESTING FALSE CACHE BOOL "CPVector Testing Enabled")	
	set(CPVECTOR_COMPILE_SORTING FALSE CACHE BOOL "Compile CPVector::Sorting")
#
######################################################################################################
# Append Source

	add_subdirectory(src)
	
	target_compile_definitions(CPVector INTERFACE ${PROJECT_NAME_UPPER}_VERSION="${PROJECT_VERSION}" )

#
######################################################################################################
# Append Examples

	if( ${CPVECTOR_BUILD_EXAMPLES} )
		message("Building ${CMAKE_PROJECT_NAME} Examples...")
		add_subdirectory(examples)
	endif()
#
######################################################################################################
# Append Tests

	if( ${CPVECTOR_TESTING} )
		message("Building ${CMAKE_PROJECT_NAME} Tests...")

		set(DOWNLOAD_EXTRACT_TIMESTAMP TRUE )
		include(FetchContent)

		FetchContent_Declare(
		  googletest
		  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
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
