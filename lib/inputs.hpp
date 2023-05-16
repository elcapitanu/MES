#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <iostream>
#include <string>
#include <stdint.h>

#include "threads/Mthread.hpp"

using std::cin;
using std::cout;
using std::endl;

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