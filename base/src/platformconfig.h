// Shree Ganeshaya Namah

/**
* @file     - platformconfig.h
* @brief    - This file abstracts the OS level functions.
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#ifndef BASE_PLATFORMCONFIG_H
#define BASE_PLATFORMCONFIG_H

void        HandleDebugError            (char * pErrMsg);
bool        CompareNSwap                (uint32_t * pDest, uint32_t pExchange, uint32_t pCompareValue);

#ifdef _WIN32

#define OS_WIN

    #if __WIN64
    #define OS_WIN_64
    #else
    #define OS_WIN_32
    #endif

#elif __APPLE__
#define OS_MAC

#elif __linux
#define OS_LINUX

#elif __unix
#define OS_UNIX

#elif __posix
#define OS_POSIX

#endif

#endif // BASE_PLATFORMCONFIG_H
