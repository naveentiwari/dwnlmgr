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
    vPageInUse      = 0;
    vOfZInPage      = sizeof(tPageHeader);
    vCurrentPage    = pFileHeader->SetThreadPage (pThrdNum);
    
    // allocate the page
    vPageSet    = (uint8_t *) AllocAligned (DISK_CONTIGUOUS_PAGE_COUNT * DISK_PAGE_SIZE, DISK_PAGE_SIZE);

    // set the header
    vPageHeader = (tPageHeader *) vPageSet;

    // set info in the header
    vPageHeader->uStartOfZ       = pStartOfZ;
    vPageHeader->uContentSize    = 0;
    vPageHeader->uNextPage       = 0;
}

/**
* @brief - Destructor to release the memory
*/
ContentPage::~ContentPage ()
{
    // release all the pages
    FreeAligned (vPageSet);
}

//void ContentPage::Write (void * pBuf, uint32_t pSize)
//{
//}

void ContentPage::PrepareToPersist ()
{
    SetPageCRC (this);
}
