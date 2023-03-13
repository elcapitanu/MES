#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include "driver.hpp"
#include "mes.hpp"

using namespace MES;

using std::cout;
using std::cin;
using std::endl;

namespace Interface
{
    class GUI
    {
    private:
        struct timeval time_now;
        uint64_t init, t, new_t, interval, fps, step, i;
        void show(Algorithm mes);
        uint64_t getMillis(struct timeval time_now);

        std::string name;
        
        time_t date;
    public:
        void ui(Algorithm mes);

        GUI(void);
        ~GUI();
    };
    
}

#endif