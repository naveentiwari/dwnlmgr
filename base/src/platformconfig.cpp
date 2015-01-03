// Shree Ganeshaya Namah

/**
* @file     - platformconfig.cpp
* @brief    - This file implements functions
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#include <base.h>

#ifdef OS_WIN
#include "platformconfig_win.cxx"
#endif // OS_WIN

#ifdef OS_MAC
#include "platformconfig_mac.cxx"
#endif // OS_MAC

#ifdef OS_LINUX
#include "platformconfig_linux.cxx"
#endif // OS_LINUX
