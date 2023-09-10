add_subdirectory(BasicFunctionality)
add_subdirectory(Constructors)
add_subdirectory(DynamicAllocation)
add_subdirectory(Operators)

if ( ${CPVECTOR_SORTING} )
	add_subdirectory(Sorting)
endif()

if ( ${CPVECTOR_EXCEPTIONS} )
	add_subdirectory(Exceptions)
endif()