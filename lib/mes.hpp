#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "tcp.hpp"
#include "opc-ua.hpp"

#include "threads/Mthread.hpp"
#include <postgresql/libpq-fe.h>


struct piece
{
    int pos = -1;
    int type = -1;
};

struct machine
{
    int tool = 0;
    int totalOperatingTime = 0;
    int operatedPieces[9] = {};
    int totalOperatedPieces = 0;
};

struct dock
{
    int unloadedPieces[9] = {};
    int totalUnloadedPieces = 0;
};

struct factory
{
    int remSpaceWar = 23;     // remaining space in warehouse
    struct piece pieces[128]; // all pieces in factory
    int total = 0;
    int p[9] = {};            // total of pieces from each type

    struct dock docks[2];
    struct machine machines[4];
};

struct dayPlan
{
    int buy[2]; // amount to buy from P1 and P2
    int work[9]; // amount to work from each Piece
    int deliver[9]; // amount to work from each Piece
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

        fac.p[0] = 15;   
        fac.p[1] = 15;   

        fac.machines[0].tool = 1;
        fac.machines[1].tool = 1;
        fac.machines[2].tool = 2;
        fac.machines[3].tool = 1;
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

    struct dayPlan plan;

    struct fifoPLC fifo;

    int parser(char *m);
    void planDay();
    void updateFactory();
    void addPiece(int type);
    void updateMachine(int machine, int newTool);
    void savePieceWarehouse();
};


class Database
    {
    private:
        const std::string kDbHostIP = "10.227.240.130"; 
        const std::string kDbName = "up201905660";
        const std::string kDbUsername = "up201905660";
        const std::string kDbPassword = "123456789";

        std::string dbconn_str = "dbname=" + kDbName + " host=" + kDbHostIP +
            " user=" + kDbUsername + " password=" + kDbPassword +
            " connect_timeout=2"; 
        int status;


    public:
        
        PGconn* dbconn = PQconnectdb(dbconn_str.c_str());

        int connectDatabase();
        int checkProgressWorking();
        void writeAlgorithm();
        void readAlgorithm();
        int CheckIsEmpty();
        void print_db(std::string db_name);
        int InsertRequest(int x);
        
        Database();
        ~Database();
    };

#endif