// Shree Ganeshaya Namah

/**
* @file     - debug.h
* @brief    - This file defines the debugging interface.
* @author   - Naveen Kumar Tiwari
* @date     - 28-12-2014
*/

#ifndef BASE_DEBUG_H
#define BASE_DEBUG_H

#ifdef  DEBUG

void                    InitializeDebug                     ();
void                    FinalizeDebug                       ();
void                    CheckAssertions                     (bool pAssertResult,
                                                             bool pExpectResult,
                                                             const char * pFile,
                                                             const char * pFunction,
                                                             uint32_t pLine);

#define BASE_DEBUG_LOG  "debug.log"

#define DERR_IF_TRUE(c)         CheckAssertions(c, true, __FILE__, __func__, __LINE__)
#define DERR_IF_NULL(c)         CheckAssertions(c, false, __FILE__, __func__, __LINE__)
#define DEBUG_ERROR             CheckAssertions(true, false, __FILE__, __func__, __LINE__)

#define VERIFY_IF_TRUE (c)      CheckAssertions(c, true, __FILE__, __func__, __LINE__)
#define VERIFY_IF_NULL (c)      CheckAssertions(c, false, __FILE__, __func__, __LINE__)

#else // DEBUG

#define DERR_IF_TRUE(c)
#define DERR_IF_NULL(c)
#define DEBUG_ERROR

#define VERIFY_IF_TRUE (c)      c
#define VERIFY_IF_NULL (c)      c
    
#endif // DEBUG

#endif // BASE_DEBUG_H
