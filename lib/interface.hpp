#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

#include "time.hpp"
#include "mes.hpp"

using std::cin;
using std::cout;
using std::endl;

namespace Interface
{
    class GUI
    {
    private:
        std::string name;

        time_t date;

    public:
        void show(MES::Algorithm mes);

        GUI(void);
        ~GUI();
    };

}

#endif