#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "tcp.hpp"
#include "opc-ua.hpp"

#include "threads/Mthread.hpp"

struct state
{
    uint32_t id;
    char transition[100];
};

struct state_mahcine
{
    state states[100];
    uint32_t curr_state;
};

class MES : public Tasks::Thread
{
public:
    MES(Socket *s, OpcUa *o)
        : soc(s), op(o)
    {
#if DEBUG_THR
        cout << "MES: ola" << endl;
#endif

        orders = 0;
        memset(order, 0, sizeof(order));
        init_t = initTime(time_now);

        day = 0;
        newDay = 0;
    }

    ~MES();

    struct timeval time_now;

    uint16_t orders;

    int day;

private:
    inline std::string getName() override
    {
        return "MES";
    }

    void onMain() override;

    Socket *soc;
    OpcUa *op;

    uint64_t init_t;

    char msg[1500];

    int newDay;

    int order[18];

    int type2pos(char *type);
    int parser(char *m);
    void planDay();
};

#endif