// Shree Ganeshaya Namah

/**
 * @file    - threadpool.cpp
 * @brief   - This file implements all the interfaces of the thread pool class
 * @author  - Naveen Kumar Tiwari
 * @date    - 25-09-2014
 */

#include <base.h>

/**
 * @brief - Constructor of the class
 *
 * @param [in] pThreadCount - number of threads in the worker pool
 */
ThreadPool::ThreadPool (uint32_t pThreadCount)
{
    // initialize all members of the class
    Initialize (pThreadCount);
}

/**
 * @brief - Destructors of the class
 */
ThreadPool::~ThreadPool ()
{
    // prepare the class for deletion
    Finalize ();
}

/**
 * @brief - This function initializes all the class members along with the worker threads
 *
 * @param [in] pThreadCount - thread count
 */
void ThreadPool::Initialize (uint32_t pThreadCount)
{
    // queue is initially empty, so set vReady to false
    vReady          = false;
    // set vContinue to true
    vContinue       = true;

    // set the thread count
    vThreadCount    = pThreadCount;

    // allocate the threads
    vThreads        = new std::thread[vThreadCount];

    // walk all the threads and set the worker functions
    for (uint32_t lndx=0; lndx<vThreadCount; ++lndx) {
        vThreads[lndx]      = std::thread (ThreadPool::StartExecution, this);
    }
}

/**
 * @brief - This function stops all the thread and de-allocates the memory
 */
void ThreadPool::Finalize ()
{
    // set continue to false, so that threads can come out of the worker functions
    vContinue = false;

    // notify all the threads to wake up
    vCV.notify_all ();

    // wait for all the threads
    for (uint32_t lndx=0; lndx < vThreadCount; ++lndx) {
        vThreads[lndx].join ();
    }

    // de-allocate the memory from thread
    delete[] vThreads;
}

/**
 * @brief - Static worker function to call the actual worker function
 *
 * @param [in] pThreadPool - thread pool pointer
 */
void ThreadPool::StartExecution (ThreadPool * pThreadPool)
{
    // call the worker function
    pThreadPool->Execute ();
}

/**
 * @brief - The worker function of the class
 */
void ThreadPool::Execute ()
{
    // set the task info
    tTaskInfo   tskinfo(NULL, NULL);

    // while the continue is true keep executing the task
    while (vContinue) {
        // scope limitation for the lock
        {
            // take a lock
            std::unique_lock<std::mutex>    lck(vSyncTaskQ);

            // while the queue is empty and the thread is allowed to run, wait for it to fill
            while (!vReady && vContinue) {
                // wait
                vCV.wait (lck);
            }

            // check if the thread was woken up by the finalize
            if (!vContinue) {
                // continue
                continue;
            }

            // get the task from the front
            tTaskInfo qtskinfo     = vTaskQ.front ();

            // set the information to higher scope variable
            tskinfo.uFunction      = qtskinfo.uFunction;
            tskinfo.uData          = qtskinfo.uData;

            // remove the task from the queue
            vTaskQ.pop ();

            // check if the queue is empty, make ready as false and notify that all the tasks are completed
            if (vTaskQ.empty()) {
                vReady = false;
                vFinishedQTasks.notify_all ();
            }
        }

        // execute the function with the data
        tskinfo.uFunction (tskinfo.uData);
    }
}

/**
 * @brief - This fuunction stops the tasks from getting queued
 *          and focuses on completing all the queued tasks.
 *          This function should be called before deleting the
 *          threadpool to ensure that all the tasks in the thread
 *          pool are executed.
 */
void ThreadPool::CompleteAllTasks ()
{
    // stop the tasks from enqueing
    vRejectTask = true;

    {
        // get a lock
        std::unique_lock<std::mutex>    lck(vSyncTaskQ);

        // wait till all the tasks are completed
        while (vReady) {
            vFinishedQTasks.wait  (lck);
        }
    }

    // set the reject task to false to allow for the task to be enqueued
    vRejectTask = false;
}

/**
 * @brief - This function is called for executing the function on the worker threads. If the 
 *
 * @param [in] pFunc - function that needs to be executed
 * @param [in] pData - data that the function would require
 */
bool ThreadPool::AsyncExecute (Run pFunc, void * pData)
{
    if (!vRejectTask) {

        // take a lock on the queue
        std::unique_lock<std::mutex>    lck(vSyncTaskQ);
     
        // set the function and data info in the object
        tTaskInfo tskinfo(pFunc, pData);

        // push the object on the queue
        vTaskQ.push (tskinfo);

        // set the ready to true
        vReady      = true;

        // wake up one thread to do the execution
        vCV.notify_one ();

        // return true since task was successfully queued
        return true;
    }

    // Unable to queue task, return false
    return false;
}
