#ifndef INPUTS_HPP
#define INPUTS_HPP

#include "../main.hpp"

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