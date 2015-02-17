// Shree Ganeshaya Namah

/**
* @file     - contentpage.cpp
* @brief    - This files contains the implementation of the ContentPage
* @author   - Naveen Kumar Tiwari
* @date     - 27-12-2014
*/

#include <disk.h>

/**
* @brief - Constructor to initialize the class members
*
* @param [in] pStartOfZ - the offset from which the content would be save in this file
*/
ContentPage::ContentPage (uint16_t pThrdNum, uint64_t pStartOfZ, FileHeader * pFileHeader)
{
    // set the page header info in this
    vFileHeader     = pFileHeader;

    vCurDiskPage    = pFileHeader->SetThreadPage (pThrdNum);
    vPageInUse      = 0;
    vOfZInPage      = DISK_PAGE_START_OFFSET;
    
    // allocate the page
    vPageSet        = (uint8_t *) AllocAligned (DISK_CONTIGUOUS_PAGE_COUNT * DISK_PAGE_SIZE, DISK_PAGE_SIZE);
    vCurPagePtr     = vPageSet;

    // set the header
    vCurPageHeader  = (tPageHeader *) vPageSet;

    // set info in the header
    vCurPageHeader->uStartOfZ       = pStartOfZ;
    vCurPageHeader->uContentSize    = 0;
    vCurPageHeader->uNextPage       = 0;
}

/**
* @brief - Destructor to release the memory
*/
ContentPage::~ContentPage ()
{
    // release all the pages
    FreeAligned (vPageSet);
}

void ContentPage::Write (void * pBuf, uint32_t pSize, SyncSList * pList)
{
        uint32_t    sizeav;

    DERR_IF_NULL (pBuf);
    DERR_IF_NULL (pList);

    sizeav  = DISK_PAGE_SIZE - vOfZInPage;

    if (sizeav > pSize) {

        memcpy (vCurPagePtr + vOfZInPage, pBuf, pSize);

        vOfZInPage += pSize;

        if (vCurPageHeader->uIsDirty)
            return;

        pList.InsertAtLast (vCurPagePtr);
    }
}

void ContentPage::PrepareToPersist ()
{
    SetPageCRC (this);
}
