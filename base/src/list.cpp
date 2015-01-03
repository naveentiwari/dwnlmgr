// Shree Ganeshaya Namah

/**
* @file     - list.cpp
* @brief    - This file implements the link list data structure.
* @author   - Naveen Kumar Tiwari
* @date     - 01-01-2015
*/

#include <base.h>

/**
* @brief - Constructor to initialize the claas members
*/
SList::SList ()
{
    // initialize head and tail to null
    vHead       = vTail = NULL;
    // make the node count to zero
    vNodeCount  = 0;
}

/**
* @brief - Delete all the node
*/
SList::~SList ()
{
    DeleteAll ();
}

/**
* @brief - Function to insert node at the end of the list
*
* @param [in] pElem - element that needs to be inserted
*/
void SList::InsertAtLast (SListElem * pElem)
{
    // element should not be null
    DERR_IF_TRUE (pElem);

    // check if the list is empty
    if (!vTail) {
        // initialize the head and tail
        vHead = vTail   = pElem;
    } else {
        // attach the element to last node
        vTail->vNext    = pElem;

        // make this as last node
        vTail           = pElem;
    }

    // increase the node count
    ++vNodeCount;
}

/**
* @brief - Function to insert the node at the beginning of the list
*
* @param [in] pElem - element that needs to be inserted
*/
void SList::InsertAtFirst (SListElem * pElem)
{
    // element should not be null
    DERR_IF_TRUE (pElem);

    // check if the list is empty
    if (!vHead) {
        // initialize the head and tail
        vHead = vTail = pElem;
    } else {
        // make next of node point to head
        pElem->vNext  = vHead;

        // make head as node
        vHead         = pElem;
    }

    // increase the node count
    ++vNodeCount;
}

/**
* @brief - Function to delete all the nodes of the list
*/
void SList::DeleteAll ()
{
        SListElem   * p;

    // loop over all the nodes
    while (vHead) {
        // copy the node
        p       = vHead;

        // move head to next
        vHead   = vHead->vNext;

        // delete the previous head
        delete (p);
    }

    // initialize the members
    vTail       = NULL;
    vNodeCount  = 0;
}

/**
* @brief - Function to delete the first node of the list
*
* @return - node deleted from the list
*/
SListElem * SList::DeleteFirst ()
{
        SListElem   * p;

    // get the head
    p           = vHead;

    // check if head is null
    if (vHead) {
        // move the head to next node
        vHead   = vHead->vNext;
        // check if the head goes to null, make the tail also null
        vTail   = vHead ? vTail : NULL;
    }

    // decrease the node count
    --vNodeCount;

    // return the removed node
    return p;
}

/**
* @brief - Function to walk the list in the forward direction
*
* @param [in] pWalkFn   - callback function
* @param [in] pData     - data required by the callback
* @param [in] pStartPos - start position
*
* @return - false if the call back returns false, true otherwise
*/
bool SList::Walk (SListWalkFunc pWalkFn, void * pData, SListElem * pStartPos)
{
        SListElem   *   p;
        bool            rc;

    // set the start position
    p = pStartPos ? pStartPos : vHead;

    // loop over the list
    while (p) {

        // call the callback
        rc = pWalkFn (p, pData);

        // if the callback returned false, return false
        if (!rc)
            return false;

        // move to the next node
        p = p->vNext;
    }

    return true;
}

/**
* @brief - The function does a recursive traversal of the list
*
* @param [in] pWalkFn - call back function of the list
* @param [in] pData - data required by the call back
* @param [in] pNode - node of the list
*
* @return - false if the call back returns false, true otherwise
*/
bool SList::WalkBackRecursive (SListWalkFunc pWalkFn, void * pData, SListElem * pNode)
{
        bool rc = true;

    // check if the node is null, this is termination for recursive loop
    if (!pNode)
        return true;

    // if the next exists, do a recursive call on the next node
    if (pNode->vNext)
        rc = WalkBackRecursive (pWalkFn, pData, pNode->vNext);

    // if the return value is true, call the callback
    if (rc)
        rc = pWalkFn (pNode, pData);

    // return the value of callbacks
    return rc;
}

/**
* @brief - Constructor to initialize the call members
*/
DList::DList ()
{
    vHead       = vTail = NULL;
    vNodeCount  = 0;
}

/**
* @brief - Destructors to release the memory
*/
DList::~DList ()
{
    DeleteAll ();
}

/**
* @brief - Function to insert the element at the start of the list
*
* @param [in] pElem - Element to be inserted
*/
void DList::InsertAtFirst (DListElem * pElem)
{
    // check if the nodes is null
    DERR_IF_NULL (pElem);

    // check if the head is null
    if (!vHead) {
        vHead = vTail = pElem;
    } else {
        // attach the node before head
        vHead->vPrev = pElem;
        pElem->vNext = vHead;

        // make the head as current
        vHead        = pElem;
    }

    // increase the node count
    ++vNodeCount;
}

/**
* @brief - Function to insert the element at the end of the list
*
* @param [in] pElem - Element to be inserted
*/
void DList::InsertAtLast (DListElem * pElem)
{
    // check if the nodes is null
    DERR_IF_NULL (pElem);

    // check if the list is empty
    if (!vTail) {
        vHead = vTail = pElem;
    } else {

        // insert the elemet at the end of the list
        vTail->vNext    = pElem;
        pElem->vPrev    = vTail;

        // move tail ahead
        vTail           = pElem;
    }

    // increase the node count
    ++vNodeCount;
}

/**
* @brief - Function to insert the node before the specified node
*
* @param [in] pElem - element to be inserted
* @param [in] pPos  - position before which the node has to be inserted
*/
void DList::InsertBefore (DListElem * pElem, DListElem * pPos)
{
    // check if the node and position is null
    DERR_IF_NULL (pElem);
    DERR_IF_NULL (pPos);

    // store the next and previous in the node
    pElem->vNext    = pPos;
    pElem->vPrev    = pPos->vPrev;

    // change the previous of position node to the current node
    pPos->vPrev     = pElem;

    // if the previous of the position node exists
    if (pPos->vPrev)
        // change its next to node
        pPos->vPrev->vNext = pElem;

    // increment the node count
    ++vNodeCount;
}

/**
* @brief - This function inserts the given node after the position node
*
* @param [in] pElem - node to be inserted
* @param [in] pPos  - node after which the insertion has to happen
*/
void DList::InsertAfter (DListElem * pElem, DListElem * pPos)
{
    // check that the node and the position are not null
    DERR_IF_NULL (pElem);
    DERR_IF_NULL (pPos);

    // update the next and previous of the node which has to be inserted
    pElem->vNext    = pPos->vNext;
    pElem->vPrev    = pPos;

    pPos->vNext     = pElem;

    if (pPos->vNext)
        pPos->vNext->vPrev = pElem;

    ++vNodeCount;
}

void DList::DeleteAll ()
{
        DListElem   * p;

    while (vHead) {

        p       = vHead;
        vHead   = vHead->vNext;

        delete (p);
    }

    vTail       = NULL;

    vNodeCount  = 0;
}

DListElem * DList::DeleteFirst ()
{
        DListElem   * p;

    p       = vHead;

    vHead   = vHead ? vHead->vNext : NULL;
    vTail   = vHead ? vTail : NULL;

    --vNodeCount;

    return p;
}

DListElem * DList::DeleteLast ()
{
        DListElem   * p;

    p       = vTail;

    vTail   = vTail ? vTail->vPrev : NULL;
    vHead   = vTail ? vHead : NULL;

    --vNodeCount;

    return p;
}

void DList::Delete (DListElem * pNode)
{
    DERR_IF_NULL (pNode);

    if (pNode->vNext)
        pNode->vNext->vPrev = pNode->vPrev;

    if (pNode->vPrev)
        pNode->vPrev->vNext = pNode->vNext;

    --vNodeCount;
}

bool DList::Walk (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos)
{
        DListElem   *   p;
        bool            rc;

    p = pStartPos ? pStartPos : vHead;

    while (p) {

        rc = pWalkFn (p, pData);

        if (!rc)
            return false;

        p = p->vNext;
    }

    return true;
}

bool DList::WalkBack (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos)
{
        DListElem   *   p;
        bool            rc;

    p = pStartPos ? pStartPos : vTail;

    while (p) {

        rc = pWalkFn (p, pData);

        if (!rc)
            return false;

        p = p->vPrev;
    }

    return true;
}

SyncSList::SyncSList ()
{
    UnLock (vLock);
}

SyncSList::~SyncSList ()
{
    DeleteAll ();
}

void SyncSList::InsertAtLast (SListElem * pElem)
{
    Lock (vLock);

    vList.InsertAtLast (pElem);

    UnLock (vLock);
}

void SyncSList::InsertAtFirst (SListElem * pElem)
{
    Lock (vLock);

    vList.InsertAtFirst (pElem);

    UnLock (vLock);
}

void SyncSList::DeleteAll ()
{
    Lock (vLock);

    vList.DeleteAll ();

    UnLock (vLock);
}

SListElem * SyncSList::DeleteFirst ()
{
        SListElem   * p;

    Lock (vLock);

    p = vList.DeleteFirst ();

    UnLock (vLock);

    return p;
}

bool SyncSList::Walk (SListWalkFunc pWalkFn, void * pData)
{
        bool rc;

    Lock (vLock);

    rc = vList.Walk (pWalkFn, pData);

    UnLock (vLock);

    return rc;
}

bool SyncSList::WalkBack (SListWalkFunc pWalkFn, void * pData)
{
        bool rc;

    Lock (vLock);

    rc = vList.WalkBack (pWalkFn, pData);

    UnLock (vLock);

    return rc;
}

SyncDList::SyncDList ()
{
    UnLock (vLock);
}

SyncDList::~SyncDList ()
{
    DeleteAll ();
}

void SyncDList::InsertAtFirst (DListElem * pElem)
{
    Lock (vLock);

    vList.InsertAtFirst (pElem);

    UnLock (vLock);
}

void SyncDList::InsertAtLast (DListElem * pElem)
{
    Lock (vLock);

    vList.InsertAtLast (pElem);

    UnLock (vLock);
}

void SyncDList::InsertAfter (DListElem * pElem, DListElem * pPos)
{
    Lock (vLock);

    vList.InsertAfter (pElem, pPos);

    UnLock (vLock);
}

void SyncDList::InsertBefore (DListElem * pElem, DListElem * pPos)
{
    Lock (vLock);

    vList.InsertBefore (pElem, pPos);

    UnLock (vLock);
}

void SyncDList::DeleteAll ()
{
    Lock (vLock);

    vList.DeleteAll ();

    UnLock (vLock);
}

DListElem * SyncDList::DeleteFirst ()
{
        DListElem * p;

    Lock (vLock);

    p = vList.DeleteFirst ();

    UnLock (vLock);

    return p;
}

DListElem * SyncDList::DeleteLast ()
{
        DListElem * p;

    Lock (vLock);

    p = vList.DeleteLast ();

    UnLock (vLock);

    return p;
}

void SyncDList::Delete (DListElem * pNode)
{
    Lock (vLock);

    vList.Delete (pNode);

    UnLock (vLock);
}

bool SyncDList::Walk (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos)
{
        bool rc;

    Lock (vLock);

    rc = vList.Walk (pWalkFn, pData, pStartPos);

    UnLock (vLock);

    return rc;
}

bool SyncDList::WalkBack (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos)
{
        bool rc;

    Lock (vLock);

    rc = vList.Walk (pWalkFn, pData, pStartPos);

    UnLock (vLock);

    return rc;
}
