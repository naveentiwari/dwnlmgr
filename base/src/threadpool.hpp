// Shree Ganeshaya Namah
/**
 * @file    - threadpool.hpp
 * @brief   - This file contains all the interfaces for the threadpool
 * @author  - Naveen Kumar Tiwari
 * @date    - 25-09-2014
 */

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

/**
 * @brief - funtion pointer that is passed to async execute
 */
typedef void    (*Run)              (void * pData);

/**
 * @name    - tTaskInfo 
 * @brief   - Structure to hold the function and related info until
 *            they are ready for execution
 */
#define ALLOC_tTaskInfo         MALLOC  tTaskInfo
struct tTaskInfo {

        /**
         * @brief - Constructor to initialize the members
         *
         * @param [in] pRun     - function that needs to be executed
         * @param [in] pData    - data that needs to be passed to the function
         */
        tTaskInfo (Run pRun, void * pData) {
            uFunction   = pRun;
            uData       = pData;
        }
        
        Run                                 uFunction;      ///< function pointer
        void                        *       uData;          ///< data for the function to execute
};

/**
 * @name    - ThreadPool 
 * @brief   - This class defines all the interfaces for using thread pool
 */
#define ALLOC_ThreadPool        CALLOC  ThreadPool
class ThreadPool {
public:

        /**
         * @brief - constructors and destructor
         */
                                            ThreadPool                  (uint32_t pThreadCount);
                                           ~ThreadPool                  ();

       /**
        * @brief - AsyncExecute for executing the functions on worker threads of the pool
        */
        bool                                AsyncExecute                (Run pFunc, void * pData);
        void                                CompleteAllTasks            ();
private:

        /**
         * @brief - Initialize and Finalize functions
         */
        void                                Initialize                  (uint32_t pThreadCount);
        void                                Finalize                    ();

        /**
         * @brief - Worker functions of the thread pool
         */
static  void                                StartExecution              (ThreadPool * pThreadPool);
        void                                Execute                     ();

        /**
         * @brief - Private methods of the class
         */
        bool                                vReady;                     ///< ready tells whether the task queue is empty or not
        bool                                vContinue;                  ///< flag to control the stop condition of the thread
        bool                                vRejectTask;                ///< flag to allow enque of tasks

#ifdef DEBUG
        uint32_t                            vThreadCount;               ///< thread count
#endif // DEBUG

        std::mutex                          vSyncTaskQ;                 ///< mutex for the queue
        
        std::condition_variable             vCV;                        ///< condition variable for waiting for tasks in queue
        std::condition_variable             vFinishedQTasks;            ///< condition variable for waiting for tasks in queue
        
        std::queue<tTaskInfo>               vTaskQ;                     ///< queue of the tasks

        std::thread                 *       vThreads;                   ///< worker thread pool
};

#endif // THREADPOOL_HPP
