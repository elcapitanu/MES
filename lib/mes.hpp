#ifndef MES_HPP
#define MES_HPP

#include "my_time.hpp"
#include "threads/Mthread.hpp"

using std::cin;
using std::cout;
using std::endl;

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
    MES()
    {
#if DEBUG_THR
        cout << "MES: ola" << endl;
#endif

        orders = 0;
        init_t = initTime(time_now);
        sprintf(message, "OLA :)\n");
    }

    ~MES();

    struct timeval time_now;

    uint64_t init_t;

    uint16_t orders;

    char message[100] = {};

    void addNumberOfOrders(uint16_t number);

private:
    inline std::string getName() override
    {
        return "MES";
    }

    void onMain() override;
};

#endif