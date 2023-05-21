#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "tcp.hpp"
#include "opc-ua.hpp"

#include "threads/Mthread.hpp"

struct piece
{
    int pos = -1;
    int type = -1;
};

struct factory
{
    int remSpaceWar = 0; // remaining space in warehouse
    struct piece pieces[128]; // all pieces in factory
    int total = 0; // total of pieces
    int p[9] = {};  // total of pieces from each type
    int m[4] = {};  // current tool in each machine
};

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
    
    struct factory fac;

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

    int order[20];

    struct fifoPLC fifo;

    int parser(char *m);
    void planDay();
    void updateFactory();
    void addPiece(int type);
    void updateMachine(int machine, int newTool);
    void savePieceWarehouse();
};

#endif