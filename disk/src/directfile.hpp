// Shree Ganeshaya Namah

/**
* @file     - directfile.hpp
* @brief    - This file contains the definition of file handling interface.
*             The writing to file is bypassing any subsequent buffers.
* @author   - Naveen Kumar Tiwari
* @date     - 31-12-2014
*/

#ifndef DISK_DIRECTFILE_HPP
#define DISK_DIRECTFILE_HPP

class DirectWrite {
    public:

                            DirectWrite         ();
                           ~DirectWrite         ();

        void                Open                (char * pFileName);
        void                Close               ();

        void                WriteAligned        (void * pBuf, uint64_t pOffset, uint32_t pWriteSize);
        void                WriteUnAligned      (void * pBuf, uint64_t pOffset, uint32_t pWriteSize);
    private:

        void        *       vAlignedBuf;
        uint32_t            vBufSize;

#ifdef OS_WIN

        HANDLE              vHandle;            ///< Open file handle
#else
        uint64_t            vFileDescriptor;    ///< file descriptor
#endif // OS_WIN
};

#endif // DISK_DIRECTFILE_HPP
