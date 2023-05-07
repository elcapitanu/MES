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
        cout << "KEY: ola" << endl;
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