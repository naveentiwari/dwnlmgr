#include <disk.h>

/**
* @brief - Constructor to initialize the class members
*/
DirectWrite::DirectWrite ()
{
    // allocate 2 page memory to support un-aligned write
    vBufSize    = DISK_PAGE_SIZE << 2;
    vAlignedBuf = AllocAligned (vBufSize, DISK_PAGE_SIZE);
}

/**
* @brief - Destructor to release memory
*/
DirectWrite::~DirectWrite ()
{
    FreeAligned (vAlignedBuf);
}

/**
 * @brief - This function opens the file
 *
 * @param [in] pFileName - File name that needs to be opened
 */
void DirectWrite::Open (char * pFileName)
{
    vHandle = CreateFile (pFileName, GENERIC_READ | GENERIC_WRITE, 0/* Open file  exclusively*/, NULL /* No security description*/,
                          OPEN_ALWAYS, FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING, NULL);

    DERR_IF_TRUE (vHandle = INVALID_HANDLE_VALUE);

    if (vHandle == INVALID_HANDLE_VALUE)
        return;
}

/**
 * @brief - This function closes the file
 */
void DirectWrite::Close ()
{
    if (vHandle != INVALID_HANDLE_VALUE)
        CloseHandle (vHandle);
}

/**
 * @brief - This function writes the aligned buffer on the disk
 *
 * @param [in] pBuf         - Aligned buffer
 * @param [in] pOffset      - offset to which this buffer has to be written
 * @param [in] pWriteSize   - size of the data that needs to be written
 */
void DirectWrite::WriteAligned (void * pBuf, uint64_t pOffset, uint32_t pWriteSize)
{
        uint32_t    hi;
        uint32_t    byteswritten = 0;

    //  get the higher 32 bits since pointer would be required
    hi = HIGH32(pOffset);

    // do a seek
    SetFilePointer (vHandle, LOW32(pOffset), (PLONG) &hi, FILE_BEGIN);

    // write the content in the file
    WriteFile (vHandle, pBuf, pWriteSize, (LPDWORD)&byteswritten, NULL);

    DERR_IF_TRUE (pWriteSize != byteswritten);
}

void DirectWrite::WriteUnAligned (void * pBuf, uint64_t pOffset, uint32_t pWriteSize)
{
        uint64_t        ofz;
        uint32_t        wrsz;

    while (pWriteSize > vBufSize) {

        memcpy (vAlignedBuf, pBuf, vBufSize);

        WriteAligned (vAlignedBuf, pOffset, vBufSize);

        pBuf        = ((void *) ((uint8_t *) pBuf) + vBufSize);
        pWriteSize -= pWriteSize;
        pOffset    += vBufSize;
    }

    memcpy (vAlignedBuf, pBuf, pWriteSize);

    WriteAligned (vAlignedBuf, pOffset, pWriteSize);
}
