// Shree Ganeshaya Namah

/**
* @file     - platformconfig_win.cpp
* @brief    - 
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#ifdef OS_WIN

/**
* @brief - This function handles the debug error in windows debugging environment
*
* @param [in] pErrMsg - Error message to be displayed
*/
void HandleDebugError (char * pErrMsg)
{
        uint32_t    rtval;

    // show the message box for debug error
    rtval = MessageBox (NULL, pErrMsg, "Debug Error!", MB_OKCANCEL);

    // if OK was not pressed, trigger a debug breakpoint
    if (rtval != 1)
        DebugBreak ();
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
        uint32_t    rtval;

    // system call
    rtval   = InterlockedCompareExchange (pDest, pExchange, pCompareValue);

    return (rtval == pExchange);
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
bool CompareNSwap (uint64_t * pDest, uint64_t pExchange, uint64_t pCompareValue)
{
        uint64_t    rtval;

    // system call
    rtval   = InterlockedCompareExchange (pDest, pExchange, pCompareValue);

    return (rtval == pExchange);
}

#endif // OS_WIN
