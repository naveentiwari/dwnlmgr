#include <base.h>

struct JobTest : public SListElem {
    public:

        JobTest(const char * pMsg) {
            uMsg = pMsg;
        }
        const char * uMsg;
};

const char * strmsg[] = { "Msg1", "Msg2", "Msg3", "Msg4", "Msg5"};
const char * nummsg[] = { "1", "2", "3", "4", "5"};
#define msg_size 6
JobList * gJL;

static void AddStrMsg ()
{
        JobTest * jt;

    for (int i=0; i<6; ++i) {

        jt = new JobTest(strmsg[i]);

        gJL->AddJob (jt);
    }

    gJL->DoneAddingOnThisThrd ();
}

static void AddNumMsg ()
{
        JobTest * jt;

    for (int i=0; i<6; ++i) {

        jt = new JobTest(nummsg[i]);

        gJL->AddJob (jt);
    }

    gJL->DoneAddingOnThisThrd ();
}

static bool PrintJob (JobTest * pJT, void *, bool)
{
    std::cout << pJT->uMsg << std::cout;

    return true;
}

static void TestFn ()
{
    JobList::ExecuteJobs (gJL, (JobFuncDef) PrintJob, NULL);
}


int main ()
{
    InitializeDebug ();
    JobList         jl(1);

    gJL = &jl;

    //std::thread jobth(TestFn);
    std::thread first(AddStrMsg);
    //std::thread second(AddNumMsg);

    jl.SoftJoin();

    FinalizeDebug ();

    return 0;
}
