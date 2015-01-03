// Shree Ganeshaya Namah

/**
* @file     - list.hpp
* @brief    - This file defines the interfaces for lock free single link list
* @author   - Naveen Kumar Tiwari
* @date     - 01-01-2015
*/

#ifndef BASE_LIST_HPP
#define BASE_LIST_HPP

class SListElem {

    public:

inline                          SListElem           ();
virtual                        ~SListElem           () {}

inline  SListElem       *       Next                ();

friend class SList;

    private:

        SListElem       *       vNext;              ///< Next node
};

class DListElem {

    public:

        /**
        * @name - Constructors and destructor of the class
        */
inline                          DListElem           ();
virtual                        ~DListElem           () {}

inline  DListElem       *       Next                ();
inline  DListElem       *       Prev                ();

friend class DList;

    private:

        DListElem       *       vNext;              ///< next node
        DListElem       *       vPrev;              ///< previous node
};

typedef bool        (*SListWalkFunc)                 (SListElem * pNode, void * pData);
typedef bool        (*DListWalkFunc)                 (DListElem * pNode, void * pData);

class SList {
    public:

        /**
        * @name - Constructors and destructor of the class
        */
                                SList               ();
                               ~SList               ();

inline  uint32_t                Nodes               ();

        /**
        * @name - Insertion functions
        */
        void                    InsertAtLast        (SListElem * pElem);
        void                    InsertAtFirst       (SListElem * pElem);

        /**
        * @name - Delete functions
        */
        void                    DeleteAll           ();
        SListElem       *       DeleteFirst         ();

        bool                    Walk                (SListWalkFunc pWalkFn, void * pData, SListElem * pStartPos = NULL);
inline  bool                    WalkBack            (SListWalkFunc pWalkFn, void * pData);

    private:

        bool                    WalkBackRecursive   (SListWalkFunc pWalkFn, void * pData, SListElem * pNode);

        SListElem       *       vHead;              ///< head of the list
        SListElem       *       vTail;              ///< tail of the list
        uint32_t                vNodeCount;         ///< number of nodes in the list
};

class DList {
    public:

        /**
        * @name - Constructors and destructor of the class
        */
                                DList               ();
                               ~DList               ();

inline  uint32_t                Nodes               ();

        /**
        * @name - Insertion functions
        */
        void                    InsertAtFirst       (DListElem * pElem);
        void                    InsertAtLast        (DListElem * pElem);
        void                    InsertAfter         (DListElem * pElem, DListElem * pPos);
        void                    InsertBefore        (DListElem * pElem, DListElem * pPos);

        /**
        * @name - Delete functions
        */
        void                    DeleteAll           ();
        DListElem       *       DeleteFirst         ();
        DListElem       *       DeleteLast          ();
        void                    Delete              (DListElem * pNode);

        bool                    Walk                (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos = NULL);
        bool                    WalkBack            (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos = NULL);

    private:

        DListElem       *       vHead;              ///< head of the list
        DListElem       *       vTail;              ///< tail of the list
        uint32_t                vNodeCount;         ///< number of nodes in the list
};

class SyncSList {
    public:

        /**
        * @name - Constructors and destructor of the class
        */
                                SyncSList           ();
                               ~SyncSList           ();

inline  uint32_t                Nodes               ();

        /**
        * @name - Insertion functions
        */
        void                    InsertAtLast        (SListElem * pElem);
        void                    InsertAtFirst       (SListElem * pElem);

        /**
        * @name - Delete functions
        */
        void                    DeleteAll           ();
        SListElem       *       DeleteFirst         ();

        bool                    Walk                (SListWalkFunc pWalkFn, void * pData);
        bool                    WalkBack            (SListWalkFunc pWalkFn, void * pData);

    private:

        SimpleLock              vLock;              ///< lock to synchronize threads
        SList                   vList;              ///< single link list
};

/**
* @name - SyncDList 
* @brief - This class provides functionalies of doubly linked list for multi-threading environment
*/
class SyncDList {
    public:

        /**
        * @name - Constructors and destructor of the class
        */
                                SyncDList           ();
                               ~SyncDList           ();

inline  uint32_t                Nodes               ();

        /**
        * @name - Insert functions
        */
        void                    InsertAtFirst       (DListElem * pElem);
        void                    InsertAtLast        (DListElem * pElem);
        void                    InsertAfter         (DListElem * pElem, DListElem * pPos);
        void                    InsertBefore        (DListElem * pElem, DListElem * pPos);

        /**
        * @name - Delete functions
        */
        void                    DeleteAll           ();
        DListElem       *       DeleteFirst         ();
        DListElem       *       DeleteLast          ();
        void                    Delete              (DListElem * pNode);

        bool                    Walk                (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos = NULL);
        bool                    WalkBack            (DListWalkFunc pWalkFn, void * pData, DListElem * pStartPos = NULL);
    private:

        /**
        * @name - Private members of the class
        */
        SimpleLock              vLock;              ///< lock to synchronize threads
        DList                   vList;              ///< Doubly linked list
};

#include "list.hxx"

#endif // BASE_LIST_HPP
