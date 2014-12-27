#ifndef BASE_MEMORYPOOLMGR_HPP
#define BASE_MEMORYPOOLMGR_HPP

#define BASE_INITIAL_POOL_SIZE      5
#define BASE_POOL_MULTIPLICATIVE    7

class MemoryPoolMgr {
    public:
                                    MemoryPoolMgr           (uint16_t pBlcSize);
                                   ~MemoryPoolMgr           ();

        void                *       Allocate                ();
        void                        Free                    (void * pAddr);

    private:

        void                *       CheckInAllPools         ();
        void                        CreateNewPool           ();

        std::mutex                  vLock;                  ///< lock for critical section

        MemoryPoolUnit      **      vPoolUnit;              ///< Pool of memory manager unit
        MemoryPoolUnit      *       vCurrentUnit;           ///< Current memory manager unit
        uint16_t                    vUnitsInPool;           ///< Number of pools created
        uint16_t                    vPoolSize;              ///< Size of the pool
        uint16_t                    vBlcSize;               ///< Size of each block
};

#endif // BASE_MEMORYPOOLMGR_HPP
