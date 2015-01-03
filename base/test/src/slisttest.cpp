#include <base.h>

struct tSListNumElem : public SListElem {
    uint32_t        uNum;
};

bool DoPrintNumElemNode (SListElem * pNode, void * pData)
{
        tSListNumElem * node;

    node = (tSListNumElem *) pNode;

    std::cout << node->uNum << std::endl;

    pData = NULL;

    return true;
}

tSListNumElem * GetNumElemNode (uint32_t pNum)
{
        tSListNumElem   * p;

    p = new tSListNumElem;

    p->uNum = pNum;

    return p;
}

void SListInsertTest ()
{
        SList               lst;
        SListElem   *       elem;

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
    //lst.InsertAtLast (NULL);

    lst.Walk (DoPrintNumElemNode, NULL);
    lst.WalkBack (DoPrintNumElemNode, NULL);

    while (lst.Nodes ()) {

        delete (lst.DeleteFirst ());
    }
}

void InitializeDebug ();
void FinalizeDebug ();

int main ()
{
    InitializeDebug ();

    SListInsertTest ();

    FinalizeDebug ();

    return 0;
}
