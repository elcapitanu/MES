#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include "../main.hpp"

#include "my_time.hpp"
#include "mes.hpp"
#include "tcp.hpp"

#include "threads/Mthread.hpp"

struct factoryMap
{
    char warehouse[9][10];
    char pos[33]; // piece type at each pos
};


struct state_machine
{
    uint16_t state;

    /* add more features to state machine */
};

class GUI : public Tasks::Thread
{
public:
    GUI(MES *mes, Socket *s, char *ptr)
        : messi(mes), soc(s), input(ptr)
    {
#if DEBUG_THR
        cout << "GUI: ola" << endl;
#endif

        name.append("Bernardo Gabriel");
    }

    ~GUI();

private:
    inline std::string getName() override
    {
        return "GUI";
    }

    void onMain() override;

    MES *messi;
    Socket *soc;
    char *input;

    void show();

    std::string name;
    time_t date;

    struct factoryMap map;
    struct state_machine display;

    void factory2map();
};

#endif