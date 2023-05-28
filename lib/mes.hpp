#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "tcp.hpp"
#include "opc-ua.hpp"
#include "database.hpp"

#include "threads/Mthread.hpp"

struct machine
{
    int tool = 0;
    int totalOperatingTime = 0;
    int operatedPieces[9] = {};
    int totalOperatedPieces = 0;
    int free = 1;
};

struct dock
{
    int unloadedPieces[9] = {};
    int totalUnloadedPieces = 0;
};

struct factory
{
    int remSpaceWar = 23; // remaining space in warehouse
    int total = 0;
    int p[9] = {}; // total of pieces from each type

    bool sensors[33] = {false};

    struct dock docks[2];
    struct machine machines[4];
};

struct dayPlan
{
    int buy[2] = {};     // amount to buy from P1 and P2
    int work[7] = {};    // amount to work from each Piece
    int deliver[9] = {}; // amount to work from each Piece
    int tool[4];
};

class MES : public Tasks::Thread
{
public:
    MES(Socket *s, OpcUa *o, Database *d)
        : soc(s), op(o), db(d)
    {
#if DEBUG_THR
        cout << "MES: ola" << endl;
#endif

        init_t = initTime(time_now);

        day = 0;

        fac.p[0] = 15;
        fac.p[1] = 15;

        fac.machines[0].tool = 1;
        fac.machines[1].tool = 1;
        fac.machines[2].tool = 2;
        fac.machines[3].tool = 1;
    }

    ~MES();

    struct timeval time_now;

    int day = 0;

    struct factory fac;

private:
    inline std::string getName() override
    {
        return "MES";
    }

    void onMain() override;

    Socket *soc;
    OpcUa *op;
    Database *db;

    uint64_t init_t;

    char msg[1500];

    struct dayPlan plan;

    int state = 0;
    bool isToActuate = false;
    int maq;
    int totaldeliv = 0;
    bool previous_S0 = false, RE_S0 = false; 
    bool previous_S11 = false, RE_S11 = false; 
    bool previous_S16 = false, RE_S16 = false; 
    bool previous_S17 = false, RE_S17 = false; 
    bool previous_S18 = false, RE_S18 = false; 
    bool previous_OkP = false, RE_OkP = false;
    bool previous_M1 = false, FE_M1 = false; 
    bool previous_M2 = false, FE_M2 = false; 
    bool previous_M3 = false, FE_M3 = false; 
    bool previous_M4 = false, FE_M4 = false;  

    void parser(char *m);
    void planDay();
    void updateFactory();
    void addPiece(int type);
    void updateMachine(int machine, int newTool);
    void savePieceWarehouse();
    void sendOrder2PLC();
    void updateState();
    int toolNeed(int final);
    int chooseMachine(int final);
    int chooseStart(int final);
    int machineTransition(int machine);
    void risingEdges();
    void updateMachinesStatus();
    void updateMessage();
};

#endif