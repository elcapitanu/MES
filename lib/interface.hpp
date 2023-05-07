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
#include "threads/ReadPipe.hpp"

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
    GUI(Pipeline::AbstractPipe<std::vector<int>> *ptr, MES *mes)
        : m_pipe(ptr), messi(mes)
    {
        name.append("Bernardo Gabriel");
    }

    ~GUI();

    MES *messi;

    char *input;

    void show();

private:
    inline std::string getName() override
    {
        return "GUI";
    }

    void onMain() override;

    Pipeline::ReadPipe<std::vector<int>> m_pipe;

    std::string name;
    time_t date;

    struct state_machine display;
};

#endif