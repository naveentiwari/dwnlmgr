#ifndef DISK_PAGEHEADERS_H
#define DISK_PAGEHEADERS_H

#define DISK_PAGE_SIZE          4096
#define GET_PAGE_OFZ(pn)        (pn << 12)
#define PAGE_HEADER_SIZE        64
#define FILE_HEADER_SIZE        sizeof(FileHeader)
#define PAGE_HEADER_SIZE        sizeof(PageHeader)

/**
 * @name    - FileHeader 
 * @brief   - This is the header page of the temporary file
 */
typedef struct FileHeader {

    uint32_t        uPageCRC;           ///< CRC of the page to detect corruption
    uint16_t        uVersion;           ///< Version of the exe
    uint16_t        uThreadCount;       ///< Number of threads that are downloading the file
}FileHeader;

/**
 * @name    - PageHeader 
 * @brief   - This is the header that is present in each page.
 */
typedef struct PageHeader {

    uint32_t        uPageCRC;           ///< CRC of the page to detect corruption
    uint32_t        uNextPage;          ///< Next page for this thread
    uint64_t        uStartOfz;          ///< starting position of download in this page
    uint16_t        uContentSize;       ///< size of the download
}PageHeader;

#endif // DISK_PAGEHEADERS_H
