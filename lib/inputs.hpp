#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "../main.hpp"

#include <iomanip>
#include <fstream>
#include <termios.h>

#include "threads/Mthread.hpp"

class KEY : public Tasks::Thread
{
public:
    KEY()
    {
#if DEBUG_THR
        cout << "KEY: ola" << endl;
#endif
    }

    ~KEY();

    char input;

private:
    inline std::string getName() override
    {
        return "KEY";
    }

    void onMain() override;
};

#endif