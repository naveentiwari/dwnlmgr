/**
* @file     - eventlist.hxx
* @brief    - This file contains the inline implementation of the job list that is event based.
* @author   - Naveen Kumar Tiwari
* @date     - 18-01-2015
*/

#ifndef BASE_JOBLIST_HXX
#define BASE_JOBLIST_HXX

/**
* @brief - This function controls the job inflow
*
* @param [in] pTakeJobs - 
*/
void JobList::TakeJobs (bool pTakeJobs)
{
    // state cannot be switched if we are waiting to join
    DERR_IF_TRUE (vWaitToJoin);

    vTakeJobs   = pTakeJobs;
}

uint32_t JobList::GetPendingJobs ()
{
    return vList.Nodes ();
}

void JobList::DoneAddingOnThisThrd ()
{
    if (vThreadsAddingJobs)
        --vThreadsAddingJobs;
}

#endif // BASE_JOBLIST_HXX
