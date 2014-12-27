/**
 * @file    - mempool.hpp
 * @brief   - This file contains the definition of fixed size memory block pool
 * @author  - Naveen Kumar Tiwari
 * @date    - 15-12-2014
 */
#ifndef BASE_MEMORYPOOLUNIT_HPP
#define BASE_MEMORYPOOLUNIT_HPP

/**
 * @name    - MemoryPoolUnit
 * @brief   - This class defines all the interfaces for memory pool unit 
 */
class MemoryPoolUnit
{
public:

        /**
         * @name    - Constructors and destructors of the class
         */
                        MemoryPoolUnit              ();
                       ~MemoryPoolUnit              ();

       void             InitializeCache             (uint16_t pBlcSize, uint32_t pTotBlcCount);

       /**
        * @name - Public interfaces of the class
        */
        void        *   Allocate                    ();
        void            Free                        (void * pAddr);

inline  bool            Cleanable                   ();
        bool            CheckAddressLimit           (void * pAddr);
inline  bool            IsUsable                    ();

inline  uint8_t     *   GetBaseAddress              ();
inline  uint8_t     *   GetLimitAddress             ();

private:

        /**
         * @name - Private methods of the class
         */
inline  uint8_t     *   GetAddress                  (uint32_t pBlcNum);
inline  uint32_t        GetIndex                    (uint8_t * pAddr);


        /**
         * @name -  Private members of the class
         */
        uint8_t     *   vStartPos;                  ///< Beginning of memory pool
        uint8_t     *   vNext;                      ///< Num of next free block

        std::mutex      vLock;                      ///< Lock

        uint32_t        vTotBlcCount;               ///< Total num of blocks
        uint32_t        vFreeBlcCount;              ///< Num of remaining blocks
        uint32_t        vInitBlcCount;              ///< Num of initialized blocks
        uint16_t        vBlcSize;                   ///< Size of each block
};

#include "mempool.hxx"

#endif // BASE_MEMORYPOOLUNIT_HPP
