// Shree Ganeshaya Namah

/**
* @file     - fileheader.hpp
* @brief    - This file defines the FileHeader class which provides an interface to handle
*             the header of the temproary file
* @author   - Naveen Kumar Tiwari
* @date     - 27-12-2014
*/

#ifndef DISK_FILEHEADER_HPP
#define DISK_FILEHEADER_HPP

#define GET_THREAD_OFFSET(t)        (sizeof(FileHeader) + (DISK_PAGE_SIZE * t))

// forward declaration of helper functions
void SetPageCRC (void * pPage);

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

 * @name  - FileHeader
 * @brief - This class defines the interfaces for handling the header for each temproary file
 */
class FileHeader {
    public:

        /**
        * @name - Constructors and Destructors
        */
                        FileHeader          (uint32_t pVersion, uint16_t pThrdCount);
                       ~FileHeader          ();

        /**
        * @name - public interfaces of the class
        */
        uint32_t        SetThreadPage       (uint16_t pThreadNum);
        uint32_t        GetNextAvPage       ();

        void            PrepareToPersist    ();

    private:

        /**
        * @name - Private methods of the class
        */
        uint32_t        vPageCRC;           ///< CRC of the page to detect corruption
        uint32_t        vNextAvPage;        ///< Next available page in this file
        SimpleLock      vLock;              ///< Lock for multithreads
        uint16_t        vVersion;           ///< Version of the exe
        uint16_t        vThreadCount;       ///< Number of threads that are downloading the file
};

#endif // DISK_FILEHEADER_HPP
