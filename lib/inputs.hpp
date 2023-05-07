#ifndef INPUTS_HPP
#define INPUTS_HPP

#include <iostream>
#include <string>
#include <stdint.h>

#include "threads/Mthread.hpp"
#include "threads/WritePipe.hpp"

using std::cin;
using std::cout;
using std::endl;

class KEY : public Tasks::Thread
{
public:
    KEY(Pipeline::AbstractPipe<std::vector<int>> *ptr)
        : m_pipe(ptr)
    {
    }

    ~KEY();

    char input;

private:
    inline std::string getName() override
    {
        return "KEY";
    }

    void onMain() override;

    Pipeline::WritePipe<std::vector<int>> m_pipe;
};

#endif