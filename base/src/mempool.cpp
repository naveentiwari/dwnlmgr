/**
 * @file    - mempool.cpp
 * @brief   - This file implements fixed size memory block pool
 * @author  - Naveen Kumar Tiwari
 * @date    - 15-12-2014
 */

/**
 * @brief - Constructor to initialize the memory pool
 *
 * @param [in] pBlcSize     - size of each memory block
 * @param [in] pTotBlcCount - total number of blocks
 */
MemoryPoolUnit::MemoryPoolUnit (uint16_t pBlcSize, uint32_t pTotBlcCount)
{
    vInitBlcCount   = 0;                // set that no blocks are initialized

    vTotBlcCount    = pTotBlcCount;     // set total number of blocks
    vFreeBlcCount   = pTotBlcCount;     // set all the block as free
    vBlcSize        = pBlcSize;         // set block size

    // allocate memory for the pool
    vStartPos       = new uint8_t[pBlcSize * pTotBlcCount];
    vNext           = vStartPos;        // set next as the first block
}

/**
 * @brief - Destructor, to release the pool memory
 */
MemoryPoolUnit::~MemoryPoolUnit ()
{
    delete vStartPos;       // clear memory pool

    vStartPos = NULL;       // set start pointer to null
}

/**
 * @brief - This function check whether this pool is usable
 *
 * @return - true if the pool is usable 
 */
bool MemoryPoolUnit::IsUsable ()
{
    return (vStartPos != NULL);
}

/**
 * @brief - This function checks if the pool is cleanable, to be used when we wish to grow the pool
 *
 * @return - true, if cleanable
 */
bool MemoryPoolUnit::Cleanable ()
{
    return (vFreeBlcCount == vTotBlcCount);
}

/**
 * @brief - This function converts the index to address
 * @todo  - Remove multiplication and divisions from the conversion functions
 *
 * @param [in] pBlcNum - the block number that needs to be converted
 *
 * @return  - address corresponding to index
 */
uint8_t * MemoryPoolUnit::GetAddress (uint32_t pBlcNum)
{
    return (vStartPos + (pBlcNum * vBlcSize));
}

/**
 * @brief   - This function converts the address to index
 * @todo    - Remove the division from this function
 *
 * @param [in] pAddr - address for which index needs to be calculated
 *
 * @return  - index of the memory address
 */
uint32_t MemoryPoolUnit::GetIndex (uint8_t * pAddr)
{
    return (((uint32_t) (pAddr - vStartPos)) / vBlcSize);
}

/**
 * @brief - This function allocates a block and gives it to the caller
 *
 * @return - address of the allocated block
 */
void * MemoryPoolUnit::Allocate ()
{
    void * mem = NULL;

    // todo: check for better (more optimized) locking mechanism
    vLock.lock ();

    // check the initialization
    if (vInitBlcCount < vTotBlcCount) {
        // link the next un-initialized node to last initialized node
        *((uint32_t *) GetAddress (vInitBlcCount)) = vInitBlcCount + 1;
        // increase the initialize count
        ++vInitBlcCount;
    }

    // check if we have free blocks
    if (vFreeBlcCount) {

        // copy the next
        mem = (void *) vNext;

        // decrease the free block count
        --vFreeBlcCount;

        // check if this was the last block
        if (vFreeBlcCount) {
            // get the next from the list and set it as next
            vNext = GetAddress (*((uint32_t *)vNext));
        } else {
            // mark the next as null
            vNext = NULL;
        }
    }

    // unlock the pool
    vLock.unlock ();

    return mem;
}

/**
 * @brief - This function frees the allocated block
 *
 * @param [in] pAddr - 
 */
void MemoryPoolUnit::Free (void * pAddr)
{
    // lock the pool
    vLock.lock ();

    // add this node to the list
    *(uint32_t *)pAddr  = vNext ? GetIndex (vNext) : vTotBlcCount;
    // update the next
    vNext               = (uint8_t *) pAddr;

    // increase the free block
    ++vFreeBlcCount;

    // release the lock
    vLock.unlock ();
}
