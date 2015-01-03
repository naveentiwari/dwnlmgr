// Shree Ganeshaya Namah

/**
* @file     - directfile.cpp
* @brief    - 
* @author   - Naveen Kumar Tiwari
* @date     - 01-01-2015
*/

#include <disk.h>

#ifdef OS_WIN
#include "directfile_win.cxx"
#else
#include "directfile_linux.cxx"
#endif // OS_WIN
