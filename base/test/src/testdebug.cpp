// Shree Ganeshaya Namah

/**
* @file     - testdebug.cpp
* @brief    - This file contains the test cases for the debug macros
* @author   - Naveen Kumar Tiwari
* @date     - 03-01-2015
*/

#include <base.h>

bool GetTrue ()
{
    return true;
}

bool GetFalse ()
{
    return false;
}

void DebugMacroCheck ()
{
    InitializeDebug ();

    DEBUG_ERROR;

    DERR_IF_TRUE (GetTrue ());
    DERR_IF_TRUE (GetFalse ());

    DERR_IF_NULL (GetTrue ());
    DERR_IF_NULL (GetFalse ());

    FinalizeDebug ();
}

int main ()
{
    DebugMacroCheck ();

    return 0;
}
