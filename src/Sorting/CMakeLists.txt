# Initialize HEADER_LIST as an empty string list
set( HEADERS_LIST_LOCAL "" )

# Append Headers
list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector_Sorting.h")
list( APPEND HEADERS_LIST "${CMAKE_CURRENT_LIST_DIR}/CPVector_SortingArray.h")

list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPVector_Sorting.h")
list( APPEND HEADERS_LIST_LOCAL "${CMAKE_CURRENT_LIST_DIR}/CPVector_SortingArray.h")


set(HEADERS_LIST "${HEADERS_LIST}" PARENT_SCOPE)

# CPVector install process
if( INSTALL STREQUAL "ON")

	install(
		FILES ${HEADERS_LIST_LOCAL} 
		DESTINATION ${CMAKE_INSTALL_PREFIX}/include/CPVector/Sorting 
	)

endif()