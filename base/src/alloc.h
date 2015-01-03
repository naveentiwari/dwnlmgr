// Shree Ganeshaya Namah

/**
* @file     - alloc.h
* @brief    - This file contains the function signature
* @author   - Naveen Kumar Tiwari
* @date     - 01-01-2015
*/

#ifndef BASE_ALLOC_H
#define BASE_ALLOC_H

void        *           AllocAligned            (uint64_t pAllocSize, uint64_t pAlignSize);
void                    FreeAligned             (void * pPtr);

#endif // BASE_ALLOC_H
