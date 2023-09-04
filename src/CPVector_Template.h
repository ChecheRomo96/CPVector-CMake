/**
 * @file CPVector_Template.h
 * @brief CPVector::vector<> class template
 */
#ifndef CROSS_PLATFFORM_VECTOR_TEMPLATE_H
#define CROSS_PLATFFORM_VECTOR_TEMPLATE_H

	#include "CPVector_BuildSettings.h"
	#include "CPVector_Move.h"
	#include "Sorting/CPVector_Sorting.h"

	namespace CPVector{


		#if defined( CPVECTOR_USING_STD_VECTOR_ALLOCATION )

		namespace {
			const char allocation_error_str[] PROGMEM_MACRO = "Error: Allocation error.";
			const char allocation_max_size_exceded_str[] PROGMEM_MACRO = "Error: Allocation error, max size exceded.";
			const char allocation_not_enough_memory_str[] PROGMEM_MACRO = "Error: Allocation error, not enough memory for the allocation.";
		}

			class allocation_error : public std::exception {
			protected:
				std::string _parentStr;
			public:

			    const char *what() const throw() {
			        return allocation_error_str;
			    }
			};

			class allocation_max_size_exceded : public CPVector::allocation_error {
			public:
			    const char *what() const throw() {
			        return allocation_max_size_exceded_str;
			    }
			};


			class allocation_not_enough_memory : public CPVector::allocation_error {
			public:
			    const char *what() const throw() {
			        return allocation_not_enough_memory_str;
			    }
			};

		#endif


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//! @brief Cross Platform Vector class. CPVector::Vector<T> is a sequence container that encapsulates dynamic size arrays.
	//! 
	//! The elements are stored contiguously, which means that elements can be accessed not only through iterators, but also using offsets to regular pointers to elements. This means that a pointer to an element of a vector may be passed to any function that expects a pointer to an element of an array.\n\n
	//! The storage of the vector is handled automatically, being expanded as needed. Vectors usually occupy more space than static arrays, because more memory is allocated to handle future growth. This way a vector does not need to reallocate each time an element is inserted, but only when the additional memory is exhausted. The total amount of allocated memory can be queried using capacity() function. Extra memory can be returned to the system via a call to shrink_to_fit()[1].\n\n
	//! Reallocations are usually costly operations in terms of performance. The reserve() function can be used to eliminate reallocations if the number of elements is known beforehand.
	//! @tparam T Data type to be used for the Dynamic Array
	
		template <class T>
		class  vector{
			protected:

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Instance Variables

	            #if defined(CPVECTOR_USING_C_ALLOCATION)
		            unsigned int _Size;
		            unsigned int _Capacity;
		            T * _Buffer;
	            #elif defined(CPVECTOR_USING_CPP_ALLOCATION)
		            unsigned int _Size;
		            unsigned int _Capacity;
		            T * _Buffer;
	            #elif defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
	            	std::vector < T > _Vector;
				#endif
			//
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			public:
				
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @name Constructors & Destructor
			//! @{
				
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Default constructor
				//!
				//! Initializes the vector to have size() = 0, the Capacity value is undefined, it's value is only bigger than size at all times. In order to reduce 
				//! the capacity of the vector see shrink_to_fit() or clear().
				
					vector(){
					#if defined(CPVECTOR_USING_C_ALLOCATION)
						_Buffer = NULL;
						_Size = 0;
						_Capacity = 0;
					#elif defined(CPVECTOR_USING_CPP_ALLOCATION)
						_Buffer = nullptr;
						_Size = 0;
						_Capacity = 0;
					#elif defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
						_Vector.resize(0);
						shrink_to_fit();
					#endif
					}     
				//!
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Resize constructor. 
				//!
				//! Resizes the container to contain count elements, does nothing if count == 0.\n\n
				//! If value parameter is not given additional default-inserted elements are appended\n 
				//! If value parameter is given additional copies of value are appended.\n
				//! @tparam count New size of the conatainer
				//! @tparam value The value to initialize the elements with

					vector(unsigned int count, const T& value = T()) : vector(){

						resize(count, value);
					}
				//!
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Copy constructor.
				//!
				//! Constructs the container with the copy of the contents of other
				//! @tparam other another container to be used as source to initialize the elements of the container with
				
					vector(const vector<T>& other) : vector(){

						resize(other.size());
						
						for(unsigned int i = 0; i < size(); i++)
						{
							(*this)[i] = other[i];
						}
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Copy constructor.
				//!
				//! Constructs the container with the copy of the contents of an array of objects of type T.
				//! @tparam pointer location of the data to copy
				//! @tparam len number of elements to copy

					vector(const T* pointer, unsigned int len): vector(){

						resize(len);
						
						for(unsigned int i = 0; i < size(); i++)
						{
							(*this)[i] = pointer[i];
						}
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// 
				//! @brief Move constructor. 
				//!
				//! Constructs the container with the copy of the contents of other
				//! @tparam pointer location of the data to copy
				//! @tparam len number of elements to copy
				
					vector(vector<T>&& source): vector(){
						clear();

					#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
						_Vector = std::move(source._Vector); //Moving an object
					#elif defined(CPVECTOR_USING_CPP_ALLOCATION) | defined(CPVECTOR_USING_C_ALLOCATION)
						_Buffer = source._Buffer;	// Copying the pointer to the buffer allocated by source
						_Size = source._Size;
						_Capacity = source._Capacity;

						source._Size = 0;
						source._Capacity = 0;

						#if defined(CPVECTOR_USING_CPP_ALLOCATION)
						source._Buffer = nullptr;
						#elif defined(CPVECTOR_USING_C_ALLOCATION)
						source._Buffer = NULL;
						#endif
					#endif
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Destructor. 
				//!
				//! Destroys all the elements amd changes the size and capacity to 0. (Releases the used memory)
				
					~vector(){
						clear();
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// std::vector Specific Constructors

					#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
						vector(std::initializer_list<T> list): vector(){
							resize(list.size());
							std::copy(list.begin(), list.end(), _Vector.begin());
						}
					#endif
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @name Operators
			//! @{
			
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// Assignment Operators

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//! @brief Assignment operator.
					//! 
					//! This operator is used to assign new contents to the container by replacing the existing contents.
					//! @tparam source Another container of the same type.
					
						vector& operator=(const vector& source){
							if(this == &source){return *this;}
							
							if(resize(source.size())){
								for(unsigned int i = 0; i < size(); i++){
									(*this)[i] = source[i];
								}
							}
								
							return *this;
						}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//! @brief Move Assignment operator.
					//! 
					//! This operator is used to assign new contents to the container by replacing the existing contents.
					//! @tparam source Another container of the same type.
					 
						vector& operator=(vector&& source){

							if(this == &source){return *this;}
							clear();

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector = std::move(source._Vector); //Moving an object
						#elif defined(CPVECTOR_USING_CPP_ALLOCATION) | defined(CPVECTOR_USING_C_ALLOCATION)
							_Buffer = source._Buffer;	// Copying the pointer to the buffer allocated by source
							_Size = source._Size;
							_Capacity = source._Capacity;

							source._Size = 0;
							source._Capacity = 0;

							#if defined(CPVECTOR_USING_CPP_ALLOCATION)
							source._Buffer = nullptr;
							#elif defined(CPVECTOR_USING_C_ALLOCATION)
							source._Buffer = NULL;
							#endif
						#endif

							return *this;
						}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// Subscript Array Operators
				
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
					//!
					//! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
					//! @tparam position Position of the element to be fetched.
					
						T& operator[](unsigned int position){

							#if defined(CPVECTOR_USING_C_ALLOCATION) || defined(CPVECTOR_USING_CPP_ALLOCATION)
								 return _Buffer[position];
							#elif defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								//allocation_max_size_excededif(position >= size()){ throw CPVector::out }
								return _Vector[position];
							#endif
						}
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//! @brief Subscript Array operator. This operator is used to reference the element present at position given inside the operator. 
					//!
					//! It is similar to the at() function, the only difference is that the at() function throws an out-of-range exception when the position is not in the bounds of the size of vector, while this operator causes undefined behavior.
					//! @tparam position Position of the element to be fetched.

					const T& operator[](unsigned int x) const{
						////////////////////////////////////////////////////////////////////////////////////////////
						// Cast Operator 
						////////////////////////////////////////////////////////////////////////////////////////////
						// Arduino and PSoC

							#if defined(CPVECTOR_USING_C_ALLOCATION)
								 return _Buffer[x];
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						//  std::vector

							#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								return _Vector[x];
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				// Comparison Operators

					/**
					 * @brief Equal to. Checks if both vectors are equal in size and in contents, it is important that the class T has defined == amd != operators.
					 * @tparam source Another container of the same type.
					 */
					bool operator==(const vector& source) const{
						if(this == &source){return 1;}
						
						if(size() != source.size()){return 0;}
						
						for(unsigned int i = 0; i < size(); i++)
						{
							if((*this)[i] != source[i])
							{return 0;}
						}
						return 1;
					}

					/**
					 * @brief Not Equal to. Checks that both vectors doesn't have the same contents, it is important that the class T has defined == amd != operators.
					 * @tparam source Another container of the same type.
					 */
					bool operator!=(const vector& source) const{
						if(this == &source){return 1;}
						
						if(size() != source.size()){return 1;}
						
						for(unsigned int i = 0; i < size(); i++)
						{
							if((*this)[i] != source[i])
							{return 1;}
						}
						return 0;
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @name Buffer Size And Resize API
			//! @{
			
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
				//!
				//! This capacity is not necessarily equal to the vector size. It can be equal or greater, with the extra space allowing to accommodate for growth without the need to reallocate on each insertion.
				//! Notice that this capacity does not suppose a limit on the size of the vector. When this capacity is exhausted and more is needed, it is automatically expanded by the container (reallocating it storage space). The theoretical limit on the size of a vector is given by member max_size.
				//! The capacity of a vector can be explicitly altered by calling member vector::reserve.
				
					uint32_t capacity() const
					{
						////////////////////////////////////////////////////////////////////////////////////////////
						// Arduino and PSoC

							#if defined(CPVECTOR_USING_C_ALLOCATION) | defined(CPVECTOR_USING_CPP_ALLOCATION)
								return _Capacity;
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						//  std::vector

							#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								return (uint32_t)_Vector.capacity();
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Returns the number of elements in the vector.
				//!
				//! This is the number of actual objects held in the vector, which is not necessarily equal to its storage capacity.
				
					uint32_t size() const
					{
						////////////////////////////////////////////////////////////////////////////////////////////
						// Arduino and PSoC

							#if defined(CPVECTOR_USING_C_ALLOCATION) | defined(CPVECTOR_USING_CPP_ALLOCATION)
								return _Size;
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						//  std::vector

							#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								return (uint32_t)_Vector.size();
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation) to a value that's greater or equal to capacity.
				//!
				//! If new_cap is greater than the current capacity(), new storage is allocated, otherwise the function does nothing.\n
				//! reserve() does not change the size of the vector.\n
				//! If after the operation the new size() is greater than old capacity() a reallocation takes place, in which case all iterators (including the end() iterator) and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.\n
				//! After a call to reserve(), insertions will not trigger reallocation unless the insertion would make the size of the vector greater than the value of capacity().\n
				
					void reserve(uint32_t new_cap){
					#if defined(CPVECTOR_USING_C_ALLOCATION) 

						if(new_cap < _Size){ return;}
						if(new_cap == 0){ clear(); return;}

						if(_Buffer == NULL){
							_Buffer = (T*)malloc(new_cap * sizeof(T));

							if(_Buffer == NULL){
								_Size = 0;
								_Capacity = 0;
							}

							_Capacity = new_cap;
						}
						else{

							T* ptr = NULL;
							
							if((ptr = (T*)malloc(new_cap * sizeof(T)) ) != NULL){

								for(uint32_t i = 0; i < _Size; i++){
									ptr[i] = _Buffer[i];
								}

								free(_Buffer );
								_Buffer = ptr;
							}
						}
					#elif defined(CPVECTOR_USING_CPP_ALLOCATION)

						if(new_cap <= _Size){ return;}
						if(new_cap == 0){ clear(); return;}

						if(_Buffer == nullptr){

							try{ _Buffer = new T[new_cap]; }
							catch(const std::bad_alloc& ex){
						        std::cout << "Memory Allocation failed, vector will remain empty.\n Exception: "<< ex.what()<< std::endl;
						        _Buffer = nullptr;
								_Size = 0;
								_Capacity = 0;
								throw std::bad_alloc;
							}
							catch(...){
						        cout << ex.what()<< endl;
							}

							_Capacity = new_cap;
						}
						else{

							T* ptr = nullptr;
							
							try{ ptr = new T[new_cap]; }
							catch(const std::bad_alloc& ex){
						        std::cout << "Memory Allocation failed, vector will kepp the size it had, with the same data.\n Exception -> "<< ex.what()<< std::endl;
								throw std::bad_alloc;
							}
							catch(...){
						        std::cout << ex.what()<< endl;
							}

							for(uint32_t i = 0; i < _Size; i++){
								ptr[i] = CPVector::move(_Buffer[i]);
							}

							delete(_Buffer );

							_Buffer = ptr;
						}
					#elif defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)

						try{
							if (new_cap > std::vector<T>::allocator_type().max_size() ){
								throw CPVector::allocation_max_size_exceded();
							}
							else{
								_Vector.reserve(new_cap);
							}
						}
						catch(const CPVector::allocation_max_size_exceded& ex){
						    throw ex;
						}
						catch(const std::logic_error& ex){
						    //handle logic_error
						    throw ex;
						}
						catch(const std::bad_alloc& ex){
						    //handle bad_alloc
						}
						catch(const std::exception& ex){
						    //catches all exceptions derived from base exception.. might seem redundant
						}
						catch(...){
						    //handle all exceptions.. doesn't buy you much over here
						    //if you catch the above exceptions... preferable at a higher level
						}
					#endif
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Requests the container to reduce its capacity to fit its size.
				//!
				//! The request is non-binding, and the container implementation is free to optimize otherwise and leave the vector with a capacity greater than its size.\n
				//! This may cause a reallocation, but has no effect on the vector size and cannot alter its elements.                     
				 
					void shrink_to_fit()
					{
						////////////////////////////////////////////////////////////////////////////////////////////
						// Arduino and PSoC

							#if defined(CPVECTOR_USING_C_ALLOCATION)
								if(_Capacity > _Size)
								{
									T* ptr = NULL;
									
									if((ptr = (T*)malloc(_Size * sizeof(T)) ) != NULL)
									{

										for(uint32_t i = 0; i < _Size; i++)
										{
											ptr[i] = _Buffer[i];
										}

										free(_Buffer );
										_Buffer = ptr;
										_Capacity = _Size;
									}
								}
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						//  std::vector

							#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								_Vector.shrink_to_fit();
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Resizes the container to contain new_size elements, does nothing if new_size == size().
				//!
				//! If the current size is greater than new_size, the container is reduced to to fit new_size elements.\n
				//! If the current size is less than count and value parameter is unused, then additional default-inserted elements are appended.
				//! If the current size is less than count and value parameter is used, then additional copies of value are appended.
				//! @tparam new_size New size of the container.
				//! @tparam value The value to initialize the new elements with.
				 
					bool resize(uint32_t new_size, const T& value = T())
					{
						if(size() == new_size){return 1;}
						
						////////////////////////////////////////////////////////////////////////////////////////////
						// Arduino and PSoC

							#if defined(CPVECTOR_USING_C_ALLOCATION)
								
								if(new_size == 0){ clear(); return 1;}

								if(new_size > _Capacity)
								{ 
									reserve(new_size); 
									if(new_size < _Capacity)
									{
										return 0;
									}
								}

								for(uint32_t i = new_size; i < _Size; i++)
								{
									_Buffer[i].~T();
								}

								auto min = (_Size<new_size) ? _Size : new_size;

								for(uint32_t i = min; i < new_size; i++)
								{
									_Buffer[i] = value;
								}

								_Size = new_size;
								
								return 1;
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						//  std::vector

							#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								
								auto OldSize = _Vector.size();

								_Vector.resize(new_size, value);

								if(OldSize > new_size)
								{
									_Vector.shrink_to_fit();
								}

								if(_Vector.size() == new_size){return 1;}
								else{return 0;}

								return ((_Vector.size() == new_size) ? true : false );

							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
					}
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//! @brief Removes all elements from the vector (which are destroyed), leaving the container with a size and capacity of 0.
				//!
				//! if ( capacity > 0 ) A reallocation is guaranteed to happen, and the vector capacity is guaranteed to change due to calling this function.
				 
					void clear()
					{
						////////////////////////////////////////////////////////////////////////////////////////////
						// Arduino and PSoC

							#if defined(CPVECTOR_USING_C_ALLOCATION)

								for(uint8_t i = 0; i < _Size; i++)
								{
									_Buffer[i].~T();
								}

								free(_Buffer);
								_Buffer = NULL;
								_Size = 0;
								_Capacity = 0;
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
						//  std::vector

							#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
								if(_Vector.size() != 0)
								{
									_Vector.resize(0);
								}
								
								_Vector.shrink_to_fit();
							#endif
						//
						////////////////////////////////////////////////////////////////////////////////////////////
					} 
				//
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @name Core functionality
			//! @{
				
				/**
				 * @brief Copies len data elements from a buffer passed by pointer.
				 *
				 * The vector can call resize(len) is Resize = 1. If after the operation the new size() is greater than old capacity() a reallocation takes place, in which case all iterators (including the end() iterator) and all references to the elements are invalidated. Otherwise only the end() iterator is invalidated.
				 * @tparam source pointer to the first element to copy.
				 * @tparam len The number of elements to copy.
				 * @tparam Resize if Resize = 1, the vector resizes to make size() = len.
				 */
				void copy(const T* source, unsigned int len, bool Resize = 0)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Cross Compatible Code

						if(Resize == 1){resize(len);}
						
						unsigned int StopCondition = ((size()<len)?size():len);
						
						for(unsigned int i = 0; i < StopCondition; i++)
						{
							(*this)[i] = source[i];
						}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				
				/**
				 * @brief Appends the given element value to the end of the container.
				 *
				 * If after the operation the new size() is greater than old capacity() a reallocation takes place.
				 * @tparam value the value of the element to append.
				 */
				void push_back(const T& value)
				{
					////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.push_back(value);
						#endif
					//
					////////////////////////////////////////////////////////////////////////////////////////////
					//  PSoC Creator and Arduino IDE

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							resize(size() + 1);
							_Buffer[size() - 1] = value;
						#endif
					//
					////////////////////////////////////////////////////////////////////////////////////////////
				}

				/**
				 * @brief Appends the given element value to the end of the container.
				 *
				 * If after the operation the new size() is greater than old capacity() a reallocation takes place.
				 * The class used must implement the proper move semantics in order for this method to be able to call a move assignment operator.
				 * @tparam value the value of the element to append.
				 */
				void push_back(T&& Rvalue)
				{
					////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.push_back(Rvalue);
						#endif
					//
					////////////////////////////////////////////////////////////////////////////////////////////
					//  PSoC Creator and Arduino IDE

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							resize(size() + 1);
							_Buffer[size() - 1] = CPVector::move(Rvalue);
						#endif
					//
					////////////////////////////////////////////////////////////////////////////////////////////
				}
				
				/**
				 * @brief Delete the element at a given index
				 *
				 * When you call this method with index >= size(), it leads to undefined behavior. The C++ standard does not specify what should happen in this scenario. Attempting to remove an element from an empty container is an error and can cause the program to crash or produce incorrect results.
				 * @tparam value the value of the element to append.
				 */
				void pop(unsigned int index)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Arduino and PSoC

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							
							for(unsigned int i = index; i < size()-1; i++)
							{
								(*this)[i] = (*this)[i+1];
							}
							resize(size()-1);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector
							
						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.erase(_Vector.begin() + index);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
				
				/**
				 * @brief Delete the first elemnt
				 *
				 * When you call this method on an empty vector, it leads to undefined behavior. The C++ standard does not specify what should happen in this scenario. Attempting to remove an element from an empty container is an error and can cause the program to crash or produce incorrect results.
				 * @tparam value the value of the element to append.
				 * @return Returns the poped value
				 */
				void pop_first()
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Arduino and PSoC

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							pop(0);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector
							
						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.erase(_Vector.begin());
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				/**
				 * @brief Delete the last elemnt
				 *
				 * When you call this method on an empty vector, it leads to undefined behavior. The C++ standard does not specify what should happen in this scenario. Attempting to remove an element from an empty container is an error and can cause the program to crash or produce incorrect results.
				 * @tparam value The value of the element to append.
				 * @return Returns the poped value
				 */
				void pop_back()
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Arduino and PSoC

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							pop(size()-1);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector
							
						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.pop_back();
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				/**
				 * @brief Inserts a new element into the container directly before pos.
				 *
				 * The element is inserted 
				 * @tparam value The value of the element to append.
				 * @tparam pos Index where the element will be appended append.
				 */
				void emplace(const T& value, unsigned int pos)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//  PSoC Creator and Arduino IDE

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							resize(_Size+1);
							for(unsigned int i = _Size-1 ; i > pos ; i--)
							{
								(*this)[i] = CPVector::move( (*this)[i-1] );
							}
							(*this)[pos] = value;
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.emplace(_Vector.begin()+pos,value);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}


				/**
				 * @brief Inserts a new element into the container directly before pos.
				 *
				 * The element is inserted 
				 * @tparam value The value of the element to append.
				 * @tparam pos Index where the element will be appended append.
				 */
				void emplace(T&& value, unsigned int pos)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//  PSoC Creator and Arduino IDE

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							resize(_Size+1);
							for(unsigned int i = _Size-1 ; i > pos ; i--)
							{
								(*this)[i] = CPVector::move( (*this)[i-1] );
							}
							(*this)[pos] = value;
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.emplace(_Vector.begin()+pos,value);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				/**
				 * @brief Swaps the elements at index_a and index_b
				 *
				 * The element is constructed through std::allocator_traits::construct, which typically uses placement-new to construct the element in-place at a location provided by the container. However, if the required location has been occupied by an existing element, the inserted element is constructed at another location at first, and then move assigned into the required location.
				 * The class used must implement the proper move semantics in order for this method to be able to call a move assignment operator.
				 * @tparam index_a the value of the first element to swap.
				 */
				void swap(unsigned int index_a, unsigned int index_b)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Parameters validation

						auto sz = size();
						if((index_a == index_b) || (index_a>=sz) || (index_b>=sz) ){return;}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//  cross compatible code
					
						T tmp = CPVector::move((*this)[index_a]);
						(*this)[index_a] = CPVector::move((*this)[index_b]);
						(*this)[index_b] = CPVector::move(tmp);
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}

				/**
				 * @brief Deletes the element at the given index from the list, if index >= size the method does nothing.
				 *
				 * The element is destroyed and erased.
				 * @tparam index The index of the element to be erased.
				 */
				void erase(unsigned int index)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Cross Compatible code

						if(index>=size()){return;}
					//
					////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.erase(_Vector.begin()+index);
						#endif
					//
					////////////////////////////////////////////////////////////////////////////////////////////
					//  PSoC Creator and Arduino IDE

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							if(index < _Size)
							{
								for(unsigned int i = index; i < _Size ;i++)
								{
									(*this)[i] = (*this)[i+1];
								}
								resize(size()-1);
							}
						#endif
					//
					////////////////////////////////////////////////////////////////////////////////////////////
				}

				/**
				 * @brief Erases the elements between both given indices
				 *
				 * The elements are destroyed and erased. The elemnts erased include (this*)[first] and (this*)[last]. If (last<=first) or (first>=size()) the method does nothing.
				 * @tparam first The index of the first element to be erased.
				 * @tparam last The index of the last element to be erased.
				 */
				void erase(unsigned int first, unsigned int last)
				{
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// Cross Compatible code

						auto sz = size();

						if((last<=first) || (first>=sz)){return;}
						if(last>=sz){last = sz-1;}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					// std::vector

						#if defined(CPVECTOR_USING_STD_VECTOR_ALLOCATION)
							_Vector.erase(_Vector.begin()+first, _Vector.begin()+last);
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//  PSoC Creator and Arduino IDE

						#if defined(CPVECTOR_USING_C_ALLOCATION)
							if(first < _Size)
							{
								auto end = (_Size<last)?_Size:last;

								for(unsigned int i = first; i < end ; i++)
								{
									(*this)[i] = (*this)[i+1];
								}
								resize(sz-1);
							}
						#endif
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				}
			//! @}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//! @name Sorting
			//! In order for these to work the class T must have declared the <, >, and the == operators.
			//! @{
			
				#if defined(CPVECTOR_SORTING_ENABLED)

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//
						/**
						 * @brief Sorts the contents of the container based on the compare function recieved.
						 *
						 * The elements are moved based on CompareFunction, in order to see an example definition of a comparing function see CPVector::Sorting::Descending<T> and CPVector::Sorting::Ascending<T>.
						 * @tparam CompareFunction Function to be used to compare values.
						 */
						void sort(const Sorting::Callback<T> CompareFunction)
						{
							_CustomSort_Helper(CompareFunction, 0, size()-1);
						}
					//    
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//
						/**
						 * @brief Sorts the contents of the container based on the CPVector::Sorting::SortingArray<T> recieved.
						 *
						 * The elements are moved based on a CPVector::Sorting::SortingArray<T>, which is an ordered list of comparing functions, this to achieve multi level sorting.
						 * @tparam laSortingArrayst Ordered list containing the sort configuration.
						 */
						void sort(const Sorting::SortingArray<T>& SortingArray)
						{
							_CustomSort_Helper(SortingArray, 0, size()-1);
						}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//
						/**
						 * @brief Sorts the contents of the container from smallest to largest
						 *
						 * The elements are moved based on CPVector::Sorting::Asscending<T>.
						 */
						void sortAscending()
						{
							sort(Sorting::Ascending);
						}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					//
						/**
						 * @brief Sorts the contents of the container from largest to smallest
						 *
						 * The elements are moved based on CPVector::Sorting::Descending<T>.
						 */
						void sortDescending()
						{
							sort(Sorting::Descending);
						}
					//
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				#endif
			//! @}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			private:

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			// Sorting Helpers

				#if defined(CPVECTOR_SORTING_ENABLED)

					void _CustomSort_Helper(const Sorting::Callback<T> CompareFunction, unsigned int lower, unsigned int upper)
					{
						// Limits check
						if(lower > upper)
						{
							unsigned int tmp = lower;
							lower = upper;
							upper = tmp;
						}

						// Calculate new Pivot
						unsigned int pivot = lower;
						pivot = _CustomSort_Partition(CompareFunction,lower,upper,pivot);
						
						// Recursive calls
						if(pivot > lower+1){_CustomSort_Helper(CompareFunction,lower,pivot-1);}
						if(pivot < upper-1)_CustomSort_Helper(CompareFunction,pivot+1,upper);
					}
					
					unsigned int _CustomSort_Partition(int8_t (*CompareFunction)(const T& a, const T& b), unsigned int lower, unsigned int upper, unsigned int pivot)
					{
						// Store Pivot value at the Highest index (upper limit)
						swap(pivot,upper);
						
						// Initialize the exchange index at the lower limit
						int index = lower;

						// Cycle through each element
						for(unsigned int i = lower ; i < upper; i++)
						{
							// Comparing the n'th element against the pivot 
							if(CompareFunction((*this)[i],(*this)[upper]) == CPVector::Sorting::Swap)
							{
								// If the element at the n'th position is lower compared to the Pivot,
								// then it is swapped to its new place and the the index counter increases.
								swap(index,i);
								index++;
							}
						}

						// Move the pivot element back to it's place
						swap(index,upper);
						return index;
					}
					
					void _CustomSort_Helper(const Sorting::SortingArray<T>& SortingArray, unsigned int lower, unsigned int upper)
					{
						// Limits check
						if(lower > upper)
						{
							unsigned int tmp = lower;
							lower = upper;
							upper = tmp;
						}

						// Sort and get new pivot index
						unsigned int pivot = lower;
						pivot = _CustomSort_Partition(SortingArray,lower,upper,lower);

						// Recursive calls
						if(pivot > lower+1){_CustomSort_Helper(SortingArray,lower,pivot-1);}
						if(pivot < upper-1)_CustomSort_Helper(SortingArray,pivot+1,upper);
					}
					
					unsigned int _CustomSort_Partition(const Sorting::SortingArray<T>& CompareVector, unsigned int lower, unsigned int upper, unsigned int pivot)
					{
						// Store Pivot value at the Highest index (upper limit)
						swap(pivot, upper);
						
						// Initialize the exchange index at the lower limit
						int index = lower;

						// Cycle through each element
						for(unsigned int i = lower ; i < upper; i++)
						{
							// Comparing the n'th element against the pivot 
							if(CompareVector.compare((*this)[i],(*this)[upper]) == CPVector::Sorting::Swap)
							{
								// If the element at the n'th position is lower compared to the Pivot,
								// then it is swapped to its new place and the the index counter increases.
								swap(index,i);
								index++;
							}
						}

						// Move the pivot element back to it's place
						swap(index,upper);
						return index;
					}
				#endif
			//
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		};
	//!
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	}


#endif//CROSS_PLATFFORM_VECTOR_TEMPLATE_H