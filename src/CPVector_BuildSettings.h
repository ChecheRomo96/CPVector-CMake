#ifndef CROSS_PLATFORM_VECTOR_BUILD_SETTINGS_H
#define CROSS_PLATFORM_VECTOR_BUILD_SETTINGS_H
    

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // CPVector Version

        #ifndef CPVECTOR_VERSION
            #define CPVECTOR_VERSION "1.0.0"
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Arduino IDE

        #if defined(Arduino_h)
            #include <Arduino.h>
            #include "CPVector_UserSetup.h"
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // AVR 
 
        #if defined(__avr__)
            #include <cstdlib>
            #define CPVECTOR_USING_C_ALLOCATION
            
            #ifndef PROGMEM_MACRO
                #include <avr/pgmspace.h>
                #define PROGMEM_MACRO PROGMEM
            #endif
        #else
            #ifndef PROGMEM_MACRO
                #define PROGMEM_MACRO
            #endif
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ESP32 
 
        #if defined(ESP32)

            #if !defined(CPVECTOR_USING_STD_ALLOCATION) && !defined(CPVECTOR_USING_C_ALLOCATION) && !defined(CPVECTOR_USING_CPP_ALLOCATION)

                #define CPVECTOR_USING_STD
            #endif

            #if defined(CPVECTOR_USING_STD)
                #include <vector>
            #elif defined(CPVECTOR_USING_C_ALLOCATION)
                #include <cstdlib>
            #endif

        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // PSoC Creator
    
        #if defined(PSOC_CREATOR)

            //#define CPVECTOR_VERSION "0.0.1"
            #include <cstdlib>

            #define CPVECTOR_USING_C_ALLOCATION
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Desktop C++
    
        #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__APPLE__) || defined(linux)
            
            #if !defined(CPVECTOR_USING_STD_ALLOCATION)
                #define CPVECTOR_USING_STD_ALLOCATION
            #endif
            

            #include <vector>
        #endif
    //
    ////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif//CROSS_PLATFORM_VECTOR_BUILD_SETTINGS_H
