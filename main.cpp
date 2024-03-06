#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// // Toplevel:
SC_MODULE(toplevel)
{
    private :

    transition<1, 1> PRE; 
    transition<1, 1> ACT; 
    transition<1, 1> RD;
    transition<1, 1> WR;
    place<1,1> IDLE, ACTIVE;

    public : 

    SC_CTOR(toplevel)
     :  PRE("PRE"), ACT("ACT"), RD("RD"), WR("WR"),
        IDLE(1), ACTIVE(0)
    {
        ACT.in.bind(IDLE);
        ACT.out.bind(ACTIVE);

        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);

        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);

        PRE.in.bind(ACTIVE);
        PRE.out.bind(IDLE);

        SC_THREAD(process);
    }

    void process()
    {
    while (true)
    {
wait(10, SC_NS);
ACT.fire();
wait(10, SC_NS);
ACT.fire();
wait(10, SC_NS);
RD.fire();
wait(10, SC_NS);
WR.fire();
wait(10, SC_NS);
PRE.fire();
wait(10, SC_NS);
ACT.fire();
sc_stop();
}
}
};

int sc_main(int, char**)
{
    toplevel t("t");

    sc_start();
    return 0;
}
