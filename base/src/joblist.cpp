/**
* @file     - eventlist.cpp
* @brief    - This file contains the implementation of the job list that is event based
* @author   - Naveen Kumar Tiwari
* @date     - 18-01-2015
*/

#include <base.h>

/**
* @brief - Constructor to initialize the class members
*/
JobList::JobList (uint32_t pThreadsAddingJobs)
{
    // set that the list is empty
    vIsEmpty        = true;
    // allow the jobs to be added
    vTakeJobs       = true;
    // allow the execution function to run
    vJobsCompleted  = false;
    // set that the jobs are incomplete
    vWaitToJoin     = false;

    vThreadsAddingJobs  = pThreadsAddingJobs;

    vSyncList.unlock ();
    vWaitMutex.unlock ();
    vKillBefore.unlock ();
}

/**
* @brief - Destructor to release the memory
*/
JobList::~JobList ()
{
}

/**
* @brief - This function add the job to the list of jobs
*
* @return 
*/
SListElem * JobList::GetJob ()
{
    // take a lock on wait mutex
    std::unique_lock<std::mutex> waitlock(vWaitMutex);

    // define scope and check if the list is empty
    // if the list is empty set the empty flag
    {
        std::lock_guard<std::mutex>  locklist(vSyncList);
        if (vList.Nodes () == 0)
            vIsEmpty    = true;
    }

    // it might happen that element has been inserted into the list
    // check if the list is still empty, wait until the list is empty
    while (vIsEmpty) {
        vCV.wait(waitlock);
    }

    // define scope and take a lock on the list and get the first element
    // from the list
    {
        std::lock_guard<std::mutex>  locklist(vSyncList);

        return vList.DeleteFirst ();
    }
}

/**
* @brief - This function adds the job to the job list
*
* @param [in] pJob - Job
*/
void JobList::AddJob (SListElem * pJob)
{
    // check if the jobs are allowed to be added
    if (!vTakeJobs) {
        // error, add job should not be called after the jobs are stoped
        DEBUG_ERROR;
        // return without adding the job
        return;
    }

    // take lock on the list
    std::lock_guard<std::mutex>  locklist(vSyncList);

    // check if the list is empty
    if (vList.Nodes() == 0) {
        // set that the list is not empty, no one will check this flag
        // because we have the lock
        vIsEmpty    = false;
        // notify the threads waiting to do the job
        vCV.notify_one ();
    }

    // insert the job at the end of he list
    vList.InsertAtLast (pJob);
}

/**
* @brief - This function is called to stop adding jobs and complete all the jobs
*/
void JobList::Join ()
{
    // take a lock on wait mutex
    std::unique_lock<std::mutex> waitlock(vKillBefore);

    // do not take any more jobs
    vTakeJobs = false;
    // set that some thread is waiting to joing
    vWaitToJoin = true;

    while (!vJobsCompleted) {
        vKillCV.wait (waitlock);
    }
    
}

/**
* @brief - This function is called to stop adding jobs and complete all the jobs
*/
void JobList::SoftJoin ()
{
    // take a lock on wait mutex
    std::unique_lock<std::mutex> waitlock(vKillBefore);

    // set that some thread is waiting to joing
    vWaitToJoin = true;

    while (!vJobsCompleted) {
        vKillCV.wait (waitlock);
    }
}

/**
* @brief - This function is called to execute the jobs of the pool
*
* @param [in] pJobs - Job pool
* @param [in] pJobFunction - Job function
* @param [in] pData - extra data required by the job function
*/
void JobList::ExecuteJobs (JobList * pJobs, JobFuncDef pJobFunction, void * pData)
{
        bool    cont;
        bool    rc;

    cont = rc = true;

    // keep looping
    while (cont) {

        // call the job function
        rc = pJobFunction (pJobs->GetJob (), pData, rc);

        // check if there are no more jobs and no more jobs are going to be added
        // stop the loop and notify all the waiting threads
        if (pJobs->GetPendingJobs () == 0 && pJobs->vThreadsAddingJobs == 0) {
            // stop the loop
            cont = false;
            // notify all the threads
            pJobs->vKillCV.notify_all ();
        }
    }
}
