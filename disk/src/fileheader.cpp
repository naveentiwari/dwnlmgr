// Shree Ganeshaya Namah

/**
* @file     - fileheader.cpp
* @brief    - This file contains the implementation of File header
* @author   - Naveen Kumar Tiwari
* @date     - 27-12-2014
*/
#include <disk.h>

/**
* @brief - Constructor to initialize the class members
*
* @param [in] pVersion      - Version of the executable
* @param [in] pThrdCount    - Set the number of thread count
*/
FileHeader::FileHeader (uint32_t pVersion, uint16_t pThrdCount)
{
    vVersion        = pVersion;
    vThreadCount    = pThrdCount;

    // first page is housekeeping, hence content starts from 2nd page onwards
    vNextAvPage     = 2;

    // initialize the lock
    UnLock (vLock);
}

/**
* @brief - This function sets the first page number of each thread
*
* @param [in] pThreadNum    - thread number
*/
uint32_t FileHeader::SetThreadPage (uint16_t pThreadNum)
{
        uint32_t     * pagenum;

    // debug check if number of thread increases the initialized number
    DERR_IF_TRUE (pThreadNum > vThreadCount);

    // get the location in the header to store the page number
    pagenum     = ((uint32_t *) this) + GET_THREAD_OFFSET(pThreadNum);

    // take a lock before changing the class members
    Lock (vLock);

    // set the page in the header
    *pagenum    = vNextAvPage;

    // increment the page number
    vNextAvPage += DISK_CONTIGUOUS_PAGE_COUNT;

    // increase the number of thread in the header
    if (pThreadNum > vThreadCount)
        vThreadCount = pThreadNum;

    // release the lock
    UnLock (vLock);

    return *pagenum;
}

/**
* @brief - Function to prepare the page for persistence
*/
void FileHeader::PrepareToPersist ()
{
    // set the CRC in the page
    SetPageCRC (this);
}

/**
* @brief - This function is used for giving the threads the page numbers to use
*
* @return - the offset
*/
uint32_t FileHeader::GetNextAvPage ()
{
        uint32_t    rtval;

    // take lock to change the class members
    Lock (vLock);

    // copy the value in a variable to return
    rtval = vNextAvPage;

    // move to next location of page
    vNextAvPage += DISK_CONTIGUOUS_PAGE_COUNT;

    // unlock
    UnLock (vLock);

    // return the page number
    return rtval;
}
