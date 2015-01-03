// Shree Ganeshaya Namah

/**
* @file     - disk.h
* @brief    - This file contain all the includes of the disk interfaces.
* @author   - Naveen Kumar Tiwari
* @date     - 27-12-2014
*/

#ifndef DISK_H
#define DISK_H

#include <base.h>

#define DISK_PAGE_SIZE              16384
#define GET_PAGE_OFZ(pn)            (pn << 12)
#define PAGE_HEADER_SIZE            64
#define DISK_CONTIGUOUS_PAGE_COUNT  16

#include <src/fileheader.hpp>
#include <src/directfile.hpp>
#include <src/contentpage.hpp>

#endif // DISK_H
