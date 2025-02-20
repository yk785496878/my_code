#pragma once

#ifndef COMM_API
    #ifdef _WIN32
        #ifdef DLL_EXPORTS
            #define COMM_API __declspec(dllexport)
        #else
            #define COMM_API __declspec(dllimport)
        #endif
    #else
        #define COMM_API
    #endif
#endif


#ifndef NS_AD
    #define BEGIN_NS_AD namespace ad{ namespace navi {
    #define END_NS_AD } }
    #define USING_NS_AD using namespace ad::navi
    #define NS_AD ad::navi
#endif

#define TRUE true
#define FALSE false