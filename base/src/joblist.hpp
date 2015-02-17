/**
* @file     - eventlist.hpp
* @brief    - This file contains the implementation of the job list that is event based.
* @author   - Naveen Kumar Tiwari
* @date     - 18-01-2015
*/

#ifndef BASE_JOBLIST_HPP
#define BASE_JOBLIST_HPP

typedef     bool    (*JobFuncDef)       (SListElem * pElem, void * pData, bool pPrevRetVal);

class JobList {
public:

                                        JobList             (uint32_t pThreadsAddingJobs);
                                       ~JobList             ();

        SListElem       *               GetJob              ();
        void                            AddJob              (SListElem * pJob);

inline  uint32_t                        GetPendingJobs      ();

inline  void                            TakeJobs            (bool pTakeJobs);

inline  void                            DoneAddingOnThisThrd();

        void                            Join                ();
        void                            SoftJoin            ();

static  void                            ExecuteJobs         (JobList * pJobs, JobFuncDef pJobFunction, void * pData);

private:

        bool                            vIsEmpty;           ///< variable to check the wait state
        bool                            vTakeJobs;          ///< variable to control the job inflow
        bool                            vJobsCompleted;     ///< All the jobs are completed
        bool                            vWaitToJoin;        ///< flag to indicate that some thread is waiting for completion of tasks

        uint32_t                        vThreadsAddingJobs; ///< Number of threads adding the job to the pool

        std::mutex                      vSyncList;          ///< Synced Insertion
        std::mutex                      vWaitMutex;         ///< mutex for condition variable
        std::mutex                      vKillBefore;        ///< wait before all the jobs are completed

        std::condition_variable         vKillCV;            ///< wait for all the jobs to complete
        std::condition_variable         vCV;                ///< condition variable to wait

        SList                           vList;              ///< list
};

#include "joblist.hxx"

#endif // BASE_JOBLIST_HPP
