// Shree Ganeshaya Namah

/**
* @file     - platformconfig_mac.cpp
* @brief    - This file implements functions
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#ifdef OS_MAC 

#include <libkern/OSAtomic.h>

#define SIGDBGERR   30

/**
* @brief - This function handles the debug error in non windows environment. The attached debugger should handle this exception
*
* @param [in] pErrMsg - Error message
*/
void HandleDebugError (char *pErrMsg)
{
    pErrMsg = NULL;

    //raise (SIGDBGERR);
}

/**
* @brief - This function does the compare and swap atomically
*
* @param [in] pDest         - the destination with which comparision has to happen and values is stored
* @param [in] pExchange     - the final value
* @param [in] pCompareValue - the initial value
*
* @return - true if the comparision was successful
*/
bool CompareNSwap (uint32_t * pDest, uint32_t pExchange, uint32_t pCompareValue)
{
    // system call
    return OSAtomicCompareAndSwapLong (pCompareValue, pExchange, (volatile long *) pDest);
}

/**
* @brief - This function does the compare and swap atomically
*
* @param [in] pDest         - the destination with which comparision has to happen and values is stored
* @param [in] pExchange     - the final value
* @param [in] pCompareValue - the initial value
*
* @return - true if the comparision was successful
*/
// bool CompareNSwap (uint64_t * pDest, uint64_t pExchange, uint64_t pCompareValue)
// {
//     // system call
//     return OSAtomicCompareAndSwapLong64 (pCompareValue, pExchange, pDest);
// }

#endif // OS_MAC
