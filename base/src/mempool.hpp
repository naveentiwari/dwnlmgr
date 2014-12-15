#ifndef BASE_MEMORYPOOLUNIT_HPP
#define BASE_MEMORYPOOLUNIT_HPP

class MemoryPoolUnit
{
    public:

                        MemoryPoolUnit              (uint16_t pBlcSize, uint32_t pTotBlcCount);
                       ~MemoryPoolUnit              ();

        uint8_t     *   Allocate                    ();
        void            Free                        (void * pAddr);

        bool            Cleanable                   ();

    private:

        uint8_t     *   GetAddress                  (uint32_t pBlcNum);
        uint32_t        GetIndex                    (uint8_t * pAddr);


        uint8_t     *   vStartPos;                  ///< Beginning of memory pool
        uint8_t     *   vNext;                      ///< Num of next free block

        std::mutex      vLock;                      ///< Lock

        uint32_t        vTotBlcCount;               ///< Total num of blocks
        uint32_t        vFreeBlcCount;              ///< Num of remaining blocks
        uint32_t        vInitBlcCount;              ///< Num of initialized blocks
        uint16_t        vBlcSize;                   ///< Size of each block
};

#endif // BASE_MEMORYPOOLUNIT_HPP
