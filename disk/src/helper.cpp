#include <disk.h>


void SetPageCRC (void * pPage)
{
    if (!pPage) {
        DERROR;
        return;
    }

    // dummy implementation
    *((uint32_t *)pPage) = 1;
}

void WritePageOnDisk (uint32_t pFD, uint32_t pPageNum, void * pPage)
{
    lseek (pFD, GET_PAGE_OFZ(pPageNum), SEEK_SET);
    write (pFD, pPage, DISK_PAGE_SIZE);
}
