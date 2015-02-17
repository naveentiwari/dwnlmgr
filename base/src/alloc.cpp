// Shree Ganeshaya Namah

/**
* @file     - alloc.cpp
* @brief    - This file contains the memory allocation wrappers
* @author   - Naveen Kumar Tiwari
* @date     - 31-12-2014
*/

#include <base.h>

/*
* @brief - This function allocates the memory that is aligned on the
*           specified boundary
*
* @param [in] pAllocSize - size of memory needed
* @param [in] pAlignSize - alignment size
*
* @return aligned memory if the system has memory
*/
void * AllocAligned (uint64_t pAllocSize, uint64_t pAlignSize)
{
        void    *   origptr;
        void    **  alignptr;

    DERR_IF_TRUE (sizeof(void *) >= pAlignSize);
    // debug check to ensure that pAlignSize has only 1 bit high
    DERR_IF_TRUE (pAlignSize & (pAlignSize -1));

    // allocate memory
    origptr = malloc (pAllocSize + pAlignSize - 1);

    // return null if the malloc failed
    if (!origptr)
       return NULL;

    // align the memory
    alignptr = (void **)(((uint64_t)(origptr) + pAlignSize - 1) & ~(pAlignSize - 1));

    // set the pointer that can be used at time of free
    alignptr[-1] = origptr;

    // return the align ptr
    return alignptr;
}

/**
 * @brief - This function releases the memory that was aligned after allocation
 *
 * @param [in] pPtr - aligned memory pointer
 */
void FreeAligned (void * pPtr)
{
    free (((void**)pPtr)[-1]);
}

void * Calloc (uint64_t pAllocSize)
{
        void    * ptr;

    ptr = Malloc (pAllocSize);

    memset (ptr, 0, pAllocSize);

    return ptr;
}

void Free (void * pPtr)
{
    free (pPtr);
    //delete pPtr;
}

StrPtr MakeString (CStrPtr pSrcStr)
{
        void    *   ptr;
        Long        len;

    len     = (StrLen (pSrcStr) + 1) * sizeof (Char);

    ptr     = Malloc (len);

    memcpy (ptr, pSrcStr, len);

    return (StrPtr)ptr;
}
