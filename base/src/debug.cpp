// Shree Ganeshaya Namah
/**
* @file     - debug.cpp
* @brief    - This file defines the functions for debugging
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#include <base.h>

#ifdef DEBUG

FILE * gDebugLog;

#ifdef  __FUNCTION__
#define __func__    __FUNCTION__
#endif // __FUNCTION__

/**
* @brief - This function is called to check the assertions in the debug exe
*
* @param [in] pAssertResult - resultant value of the expression
* @param [in] pExpectResult - expected value from the expression
* @param [in] pFile         - file in which this expression was written
* @param [in] pFunction     - function name
* @param [in] pLine         - line which contains this expression
*/
void CheckAssertions (bool pAssertResult, bool pExpectResult, const char * pFile, const char * pFunction, uint32_t pLine)
{
        char        buf[MAX_TXT_BUF];

    // if the expected result does not match the actual result, give debug errors
    if (pAssertResult != pExpectResult) {

        // make the error string
        sprintf (buf, "Debug Error: Expression failed in function %s of file %s(%d).\n", pFunction, pFile, pLine);
        // log into the debug log file
        fprintf (gDebugLog, "Debug Error: Expression failed in function %s of file %s(%d).\n", pFunction, pFile, pLine);
        // show the error on the error console
        fprintf (stderr, "Debug Error: Expression failed in function %s of file %s(%d).\n", pFunction, pFile, pLine);

        // handle this debug error
        HandleDebugError (buf);
    }
}

#endif // DEBUG

/**
* @brief - This function initializes the debug log file
*/
void InitializeDebug ()
{
#ifdef DEBUG
    gDebugLog = fopen (BASE_DEBUG_LOG, "a");
#endif // DEBUG
}

/**
* @brief - This function closes the debug log file
*/
void FinalizeDebug ()
{
#ifdef DEBUG
    fclose (gDebugLog);
#endif
}
