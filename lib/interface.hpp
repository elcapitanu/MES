#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "my_time.hpp"
#include "mes.hpp"

#include "threads/Mthread.hpp"

using std::cin;
using std::cout;
using std::endl;

struct state_machine
{
    uint16_t state;

    /* add more features to sate machine */
};

class GUI : public Tasks::Thread
{
public:
    GUI(MES *mes, char *ptr)
        : messi(mes), input(ptr)
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
    char *input;

    void show();

    std::string name;
    time_t date;

    struct state_machine display;
};

#endif