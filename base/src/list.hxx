// Shree Ganeshaya Namah

/**
* @file     - list.hxx
* @brief    - Inline function declarations
* @author   - Naveen Kumar Tiwari
* @date     - 03-01-2015
*/

#ifndef BASE_LIST_HXX
#define BASE_LIST_HXX

/**
* @brief - Constructor
*/
SListElem::SListElem ()
{
    vNext = NULL;
}

/**
* @brief - function to return the next of single link list
*
* @return - next of list
*/
SListElem * SListElem::Next ()
{
    return vNext;
}

/**
* @brief - This function returns the number of nodes in the list
*
* @return 
*/
uint32_t SList::Nodes ()
{
    return vNodeCount;
}

/**
* @brief - Function to walk the list back
* @note  - This function does a recursive call to do a walk back
*
* @param [in] pWalkFn - call back function
* @param [in] pData - data required by callback
*
* @return - false if the call back returns false, true otherwise
*/
bool SList::WalkBack (SListWalkFunc pWalkFn, void * pData)
{
    // do a recursive call back
    return WalkBackRecursive (pWalkFn, pData, vHead);
}

/**
* @brief - Destructor
*/
DListElem::DListElem ()
{
    vNext = NULL;
    vPrev = NULL;
}

/**
* @brief - function to return the next of doubly link list
*
* @return - next of list
*/
DListElem * DListElem::Next ()
{
    return vNext;
}

/**
* @brief - function to return th previous of the doubly link list
*
* @return - previous of list
*/
DListElem * DListElem::Prev ()
{
    return vPrev;
}

/**
* @brief - This function returns the number of nodes in the list
*
* @return 
*/
uint32_t DList::Nodes ()
{
    return vNodeCount;
}

/**
* @brief - Function to return the number of nodes in the list
*
* @return - number of nodes in the list
*/
uint32_t SyncSList::Nodes ()
{
    return vList.Nodes ();
}

/**
* @brief - Function to return the number of nodes in the list
*
* @return - number of nodes in the list
*/
uint32_t SyncDList::Nodes ()
{
    return vList.Nodes ();
}

#endif // BASE_LIST_HXX
