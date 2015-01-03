#include <base.h>

#define LOOP_COUNT      100000000

typedef void (*EvaluationFn) ();

void DoAllocateUnitPool ()
{
    void * ptr;

    uint32_t count = LOOP_COUNT;

    MemoryPoolUnit  spool;
    spool.InitializeCache (4096, 1000);

    while (count > 0) {
        ptr = spool.Allocate ();
        spool.Free (ptr);
        --count;
    }
}

void DoAllocateMgrPool ()
{
    void * ptr;
    uint32_t count = LOOP_COUNT;
    MemoryPoolMgr   pool(4096);

    while (count > 0) {
        ptr = pool.Allocate ();
        pool.Free (ptr);
        --count;
    }
}

void DoAllocationSystem ()
{
    char * ptr;
    uint32_t count = LOOP_COUNT;

    while (count > 0) {
        ptr = new char[4096];
        delete[] ptr;
        --count;
    }
}

void CheckFunctionTime (EvaluationFn pFn)
{
    clock_t     t = clock ();

    pFn();

    t = clock() -t;

    std::cout << t << " clicks" << std::endl;
}

int main ()
{
    std::cout << "System function\t\t";
    CheckFunctionTime (DoAllocationSystem);
    std::cout << "Unit pool function\t";
    CheckFunctionTime (DoAllocateUnitPool);
    std::cout << "Manager function\t";
    CheckFunctionTime (DoAllocateMgrPool);

    return 0;
}
