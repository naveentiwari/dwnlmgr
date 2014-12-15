#include <disk.h>

FileHeader::FileHeader (uint32_t pVersion, uint16_t pThrdCount);
{
    uVersion        = pVersion;
    uThreadCount    = pThrdCount;

    uNextAvPage     = 2;
}

void FileHeader::SetThreadPage (uint16_t pThreadNum, uint32_t pPageNum)
{
        uint32_t     * pagenum;

    pagenum     = ((uint8_t *) this) + GET_THREAD_OFFSET(pThreadNum);

    *pagenum    = pPageNum;
}
