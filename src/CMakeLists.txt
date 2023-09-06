######################################################################################################
# Store this directory as a variable called MCC_SRC_DIRECTORY to reference in deeper directories

	set( CPVECTOR_SRC_DIRECTORY  ${CMAKE_CURRENT_LIST_DIR})
#
######################################################################################################
# Initialize MCC_SOURCES and HEADER_LIST as an empty string list

	set( HEADERS_LIST "" )
#
######################################################################################################
# Append Sources and Headers

	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector_BuildSettings.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector_Template.h")
	list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector_Move.h")

	if( ${CPVECTOR_EXCEPTIONS} )
		list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector_Exceptions.h")
	endif()
#
######################################################################################################
# Add Subdirectories

	if( ${CPVECTOR_SORTING} )
		message("Building CPVector::Sorting...")
		add_subdirectory(Sorting)
	endif()
#
######################################################################################################
# Create the CPVector library

	add_library(CPVector INTERFACE)
	#set_target_properties(CPVector PROPERTIES LINKER_LANGUAGE CXX)
#
######################################################################################################
# Add Compliler Definitions

	if(${CPVECTOR_SORTING})
		message("CPVector::Sorting Enabled")
		target_compile_definitions(CPVector INTERFACE CPVECTOR_SORTING_ENABLED)
	endif()

	if( ${CPVECTOR_EXCEPTIONS} )
		message("CPVector exceptions enabled")
		target_compile_definitions(CPVector INTERFACE CPVECTOR_EXCEPTIONS_ENABLED)
	endif()

	if( ${CPVECTOR_ALLOCATION_METHOD} STREQUAL "std::vector" )
		message("Using std::vector for allocation")
		target_compile_definitions(CPVector INTERFACE CPVECTOR_USING_STD_VECTOR_ALLOCATION)
	elseif( ${CPVECTOR_ALLOCATION_METHOD} STREQUAL "CPP" )
		message("Using C++ allocators (new, new[], delete, delete[]")
		target_compile_definitions(CPVector INTERFACE CPVECTOR_USING_CPP_ALLOCATION)
	elseif( ${CPVECTOR_ALLOCATION_METHOD} STREQUAL "C" )
		message("Using C allocators (malloc, calloc, free)")
		target_compile_definitions(CPVector INTERFACE CPVECTOR_USING_C_ALLOCATION)
	endif()
	



#
######################################################################################################
# Include directories for install and for build 

	target_include_directories( 
		CPVector INTERFACE 
		$<INSTALL_INTERFACE:include/CPVector> 
		$<BUILD_INTERFACE:${CPVECTOR_SRC_DIRECTORY}> 
	)
#
######################################################################################################
# Add libs Subdirectory

	if( CPVECTOR_INSTALL STREQUAL "ON")

		install(
			FILES ${HEADERS_LIST} 
			DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPVector 
		)

		install(
			TARGETS CPVector 
			EXPORT CPVectorExport
			DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPVector
		)

		install(
			EXPORT CPVectorExport
			FILE CPVector-config.cmake
			DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/CPVector
		)
	endif()
#
######################################################################################################