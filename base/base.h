// shree Ganeshaya Namah
/**
 * @file    - base.h
 * @brief   - This file includes all the files that make up for the base
 * @author  - Naveen Kumar Tiwari
 * @date    - 25-09-2014
 */

#ifndef BASE_H
#define BASE_H

#define MAX_TXT_BUF             2048
#define DEFAULT_SLEEP_TIME      1
#define LOW32_MASK              (0x0000ffff)

#define LOW32(n)                (n & LOW32_MASK)
#define HIGH32(n)               (n >> 32)

/*
 * @breif   - standard include files
 */
#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <thread>
#include <bitset>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <unistd.h>

//#define uint32_t    long;
//#define uint64_t    long long;

typedef uint32_t SimpleLock;

#include "src/platformconfig.h"
#include "src/debug.h"
#include "src/lock.hpp"
#include "src/alloc.h"
#include "src/list.hpp"
#include "src/mempool.hpp"
#include "src/mempoolmgr.hpp"
#include "src/threadpool.hpp"

#endif // BASE_H
