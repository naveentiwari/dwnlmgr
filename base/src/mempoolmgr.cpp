#include <base.h>

/**
 * @brief - Constructor to initialize the members of the class
 */
MemoryPoolMgr::MemoryPoolMgr (uint16_t pBlcSize)
{
    // allocate the pool
    vPoolUnit       = new MemoryPoolUnit*[BASE_INITIAL_POOL_SIZE];

    // current pool unit as first
    vPoolUnit[0]    = new MemoryPoolUnit;
    vCurrentUnit    = vPoolUnit[0];
    vCurrentUnit->InitializeCache (pBlcSize, 1 << BASE_POOL_MULTIPLICATIVE);

    // set the pool size
    vPoolSize       = BASE_INITIAL_POOL_SIZE;
    // set the units in use as 1
    vUnitsInPool    = 1;
    // set the block size
    vBlcSize        = pBlcSize;
}

/**
 * @brief - Destructor to deallocate the pool
 */
MemoryPoolMgr::~MemoryPoolMgr ()
{
    // loop over the array and delete each pool
    for (uint16_t ndx = 0; ndx < vUnitsInPool; ++ndx) {
        delete vPoolUnit[ndx];
    }

    // delete the pool array
    delete vPoolUnit;
}

/**
 * @brief - This function is called when the current pool has failed to allocate.
 *
 * @return - memory pointer
 */
void * MemoryPoolMgr::CheckInAllPools ()
{
        void * mem = NULL;

    // take lock
    vLock.lock ();

    // loop over all the pools and try to allocate
    for (uint16_t ndx=0; ndx < vUnitsInPool; ++ndx) {
        // allocate from the pool
        mem     = vPoolUnit[ndx]->Allocate ();

        // if allocation is successful, set and return
        if (mem) {
            // set this as current pool
            vCurrentUnit = vPoolUnit[ndx];
            // release lock
            vLock.unlock ();
            // return the pointer
            return mem;
        }
    }

    // unable to allcoate the memory from any pool
    CreateNewPool ();

    // release lock
    vLock.unlock ();

    // allocate the memory from the current pool
    return Allocate ();
}

/**
 * @brief   - This function creates a new pool and sets it as current pool
 * @note    - This function should always be executed under lock
 */
void MemoryPoolMgr::CreateNewPool ()
{
        uint16_t size = vUnitsInPool + 1;

    // check if we need to increase memory pool array
    if (vUnitsInPool >= vPoolSize) {
        // increase the array size
        vUnitsInPool += BASE_INITIAL_POOL_SIZE;

        // allocate new array
        MemoryPoolUnit ** tmp = new MemoryPoolUnit*[vUnitsInPool];

        // copy at new location
        memcpy (tmp, vPoolUnit, vPoolSize * sizeof (MemoryPoolUnit *));

        // delete the old array
        delete[] vPoolUnit;
        // assign the new array
        vPoolUnit = tmp;
    }

    // initialize pointer to zero
    vPoolUnit[vUnitsInPool] = NULL;

    // loop until the OS allocates the cache, and after each call reduce the size
    while (size > 0) {
        // allocate the pool
        vPoolUnit[vUnitsInPool] = new MemoryPoolUnit;
        
        // check if the pool class was successfully allocated
        if (vPoolUnit[vUnitsInPool] == NULL) {
            // unable to allocate even the object, system out of memory
            size = 0;
            // return
            return;
        }

        // allcoate cahce
        vPoolUnit[vUnitsInPool]->InitializeCache (vBlcSize, size << BASE_POOL_MULTIPLICATIVE);

        // check if the cache was allocate
        if (vPoolUnit[vUnitsInPool]->IsUsable () == false) {
            // cache not allocated, delete class
            delete vPoolUnit[vUnitsInPool];

            vPoolUnit[vUnitsInPool] = NULL;
        } else {
            // set this as current pool
            vCurrentUnit = vPoolUnit[vUnitsInPool];
            // increase the units in pool
            ++vUnitsInPool;
            // all done
            break;
        }

        // reduce the cache size
        --size;
    }

    // not able to allocate
    if (!size) {
        //DERROR;
        return;
    }
}

/**
 * @brief - This function allocates memory from any of the pools
 *
 * @return 
 */
void * MemoryPoolMgr::Allocate ()
{
        void * mem = NULL;

    // allocate from the current pool
    mem     = vCurrentUnit->Allocate ();

    // check if the allocation was successful
    if (!mem) {
        // try other pool, if not create a new pool
        return CheckInAllPools ();
    }

    // return the allocation
    return mem;
}

/**
 * @brief - This function release the memory back to the pool
 *
 * @param [in] pAddr - memory to be release to the pool
 */
void MemoryPoolMgr::Free (void * pAddr)
{
    // check if the address belongs to the current pool
    if (vCurrentUnit->CheckAddressLimit (pAddr)) {
        // release the memory and return
        vCurrentUnit->Free (pAddr);
        return;
    }

    // take lock since vPoolUnit would be accessed
    vLock.lock ();

    // loop over all the pools
    for (uint16_t ndx=0; ndx < vUnitsInPool; ++ndx) {

        // check if the address belongs to this pool
        if (vPoolUnit[ndx]->CheckAddressLimit (pAddr)) {
            // release the memory and return
            vPoolUnit[ndx]->Free (pAddr);
            // release the lock0
            vLock.unlock ();
            // return
            return;
        }
    }

    // unlock, there was some error
    vLock.unlock ();
    // give debug error
    //DERROR;
}
