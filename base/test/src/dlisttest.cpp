#include <base.h>

struct tDListNumElem : public DListElem {
    uint32_t        uNum;
};

bool DoPrintNumElemNode (DListElem * pNode, void * pData)
{
        tDListNumElem * node;

    node = (tDListNumElem *) pNode;

    std::cout << node->uNum << std::endl;

    pData = NULL;

    return true;
}

tDListNumElem * GetNumElemNode (uint32_t pNum)
{
        tDListNumElem   * p;

    p = new tDListNumElem;

    p->uNum = pNum;

    return p;
}

void DListInsertTest ()
{
        SyncDList               lst;
        DListElem   *       elem;

    lst.InsertAtFirst (GetNumElemNode (5));
    lst.InsertAtFirst (GetNumElemNode (6));
    lst.InsertAtFirst (GetNumElemNode (7));
    lst.InsertAtFirst (GetNumElemNode (8));
    lst.InsertAtFirst (GetNumElemNode (9));
    
    lst.InsertAtLast (GetNumElemNode (4));
    lst.InsertAtLast (GetNumElemNode (3));
    lst.InsertAtLast (GetNumElemNode (2));
    lst.InsertAtLast (GetNumElemNode (1));
    lst.InsertAtLast (GetNumElemNode (0));

    lst.Walk (DoPrintNumElemNode, NULL);
    lst.WalkBack (DoPrintNumElemNode, NULL);

    while (lst.Nodes ()) {

        delete (lst.DeleteFirst ());
    }

    lst.InsertAtFirst (GetNumElemNode (5));
    lst.InsertAtFirst (GetNumElemNode (6));
    lst.InsertAtFirst (GetNumElemNode (7));
    lst.InsertAtFirst (GetNumElemNode (8));
    lst.InsertAtFirst (GetNumElemNode (9));
    
    lst.InsertAtLast (GetNumElemNode (4));
    lst.InsertAtLast (GetNumElemNode (3));
    lst.InsertAtLast (GetNumElemNode (2));
    lst.InsertAtLast (GetNumElemNode (1));
    lst.InsertAtLast (GetNumElemNode (0));

    lst.Walk (DoPrintNumElemNode, NULL);
    lst.WalkBack (DoPrintNumElemNode, NULL);

    while (lst.Nodes ()) {

        delete (lst.DeleteLast ());
    }
}

int main ()
{
    InitializeDebug ();

    DListInsertTest ();

    FinalizeDebug ();

    return 0;
}
