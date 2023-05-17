#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "tcp.hpp"
#include "opc-ua.hpp"

#include "threads/Mthread.hpp"

struct message2PLC
{
    /* content of message */
};

struct orderPLC
{
    int pos;
    struct orderPLC *next;

    struct message2PLC;
};

struct fifoPLC
{
    int total;

    struct orderPLC *first;
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

    int orders;
    int ordersLeft;

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

    struct fifoPLC fifo;

    int type2pos(char *type);
    int parser(char *m);
    void planDay();
};

#endif