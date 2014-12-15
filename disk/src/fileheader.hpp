#ifndef DISK_FILEHEADER_HPP
#define DISK_FILEHEADER_HPP

#define GET_THREAD_OFFSET(t)    (sizeof(FileHeader) + (DISK_PAGE_SIZE * t))

/**
 * @name    - FileHeader 
 * #brief   - This class provides all the functionalities for the header page of temporary file.
 *            The structure for this page is depicted below
 *
 *  _____________________________________________________________________________________________________________________
 *  |             |                     |         |              |                           |             |             |
 *  | CRC of page | Next available Page | Version | Thread count | First page of each thread | Destination | Source Info |
 *  |_____________|_____________________|_________|______________|___________________________|_____________|_____________|
 *
*/

/**

 * @brief - 
 */
class FileHeader {
    public:

                        FileHeader          (uint32_t pVersion, uint16_t pThrdCount);
        void            SetThreadPage       (uint16_t pThreadNum, uint32_t pPageNum);
    private:



        uint32_t        uPageCRC;           ///< CRC of the page to detect corruption
        uint32_t        uNextAvPage;        ///< Next available page in this file
        uint16_t        uVersion;           ///< Version of the exe
        uint16_t        uThreadCount;       ///< Number of threads that are downloading the file
};

#endif // DISK_FILEHEADER_HPP
