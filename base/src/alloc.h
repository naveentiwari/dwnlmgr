// Shree Ganeshaya Namah

/**
* @file     - alloc.h
* @brief    - This file contains the function signature
* @author   - Naveen Kumar Tiwari
* @date     - 01-01-2015
*/

#ifndef BASE_ALLOC_H
#define BASE_ALLOC_H

#define     Malloc(x)           malloc (x)
#define     MallocString(x)     malloc ((x) * sizeof(Char))
#define     CallocString(x)     (StrPtr) Calloc ((x) * sizeof(Char))

void        *           AllocAligned            (uint64_t pAllocSize, uint64_t pAlignSize);

void        *           Calloc                  (uint64_t pAllocSize);
void                    Free                    (void * pPtr);

StrPtr                  MakeString              (CStrPtr pSrcStr);

void                    FreeAligned             (void * pPtr);

#endif // BASE_ALLOC_H
