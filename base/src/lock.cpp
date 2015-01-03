// Shree Ganeshaya Namah

/**
* @file     - lock.cpp
* @brief    - This file contains the simple lock implementation
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#include <base.h>

void Lock (SimpleLock &pLock)
{
    while (CompareNSwap (&pLock, 0, 1)) {
        sleep (DEFAULT_SLEEP_TIME);
    }
}

void UnLock (SimpleLock &pLock)
{
    CompareNSwap (&pLock, 1, 0);
}
