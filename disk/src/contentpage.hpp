// Shree Ganeshaya Namah

/**
* @file     - contentpage.hpp
* @brief    - This file defines the interfaces used by the content pages
* @author   - Naveen Kumar Tiwari
* @date     - 27-12-2014
*/

struct tPageHeader : public SListElem {
        uint32_t                uPageCRC;           ///< crc of the page to detect corruption
        uint32_t                uNextPage;          ///< next page for this thread
        uint64_t                uStartOfZ;          ///< starting position of download in this page
        uint32_t                uPageNum;           ///< page number on the disk
        uint16_t                uContentSize;       ///< size of the download
        uint8_t                 uIsDirty;           ///< dirty flag
};

#define     DISK_PAGE_START_OFFSET      (sizeof (tPageHeader))
#define     DISK_PAGE_AVAILABLE_SIZE    (DISK_PAGE_SIZE - DISK_PAGE_START_OFFSET)

/**
* @name     - ContentPage 
* @brief    - This class defines all the interfaces for writing the content downloaded by thread in temproary file
*/
class ContentPage {
    public:
                                ContentPage         (uint16_t pThrdNum, uint64_t pStartOfZ, FileHeader * pFileHeader);
                               ~ContentPage         ();

        void                    Write               (void * pBuf, uint32_t pSize);
        void                    PrepareToPersist    ();
    private:

        tPageHeader *           vCurPageHeader;     ///< Page header
        uint8_t     *           vPageSet;           ///< set of allocated pages
        uint8_t     *           vCurPagePtr;        ///< Current page
        FileHeader  *           vFileHeader;        ///< File header

        uint32_t                vCurDiskPage;       ///< Current page that is been written
        uint16_t                vPageInUse;         ///< current memory page in use
        uint16_t                vOfZInPage;         ///< Offset in page that is availabe
};
