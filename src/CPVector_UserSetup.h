#ifndef CPVECTOR_USER_SETUP_H
#define CPVECTOR_USER_SETUP_H

	

	//////////////////////////////////////////////////////
	// ESP32 Only
		#if defined(ESP32)
			#define CPVECTOR_USING_STD
		#endif
	//
	//////////////////////////////////////////////////////
	//
		#if defined(__avr__)
			#define CPVECTOR_USING_C
		#endif
	//
	//////////////////////////////////////////////////////

	//#define CPVECTOR_SORTING_ENABLED



#endif//CPVECTOR_USER_SETUP_H