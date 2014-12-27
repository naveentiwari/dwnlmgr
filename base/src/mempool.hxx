#ifndef BASE_MEMORYPOOLUNIT_HXX
#define BASE_MEMORYPOOLUNIT_HXX

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
 * @brief - This function return the base address of the pool.
 *          Used specifically for testing if the address belongs to this pool
 *
 * @return - base address
 */
uint8_t * MemoryPoolUnit::GetBaseAddress ()
{
    return vStartPos;
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
 * @brief - This function return the top limit of the addess of this pool
 *          Used specifically for testing if the address belongs to this pool
 *
 * @return - upper limit of the address
 */
uint8_t * MemoryPoolUnit::GetLimitAddress ()
{
    return (GetAddress(vTotBlcCount) + vBlcSize);
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

#endif // BASE_MEMORYPOOLUNIT_HXX
