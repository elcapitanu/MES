#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>

namespace Interface
{
    class GUI
    {
    private:
        struct timeval time_now;
        uint64_t init, t, new_t, interval, fps, step, i;
        void show(void);
        uint64_t getMillis(struct timeval time_now);
    public:
        void ui(void);

        GUI(void);
        ~GUI();
    };
    
}

#endif