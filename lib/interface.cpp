#include "interface.hpp"
#include "driver.hpp"

#include <sys/time.h>
#include <stdint.h>

using namespace Interface;

uint64_t GUI::getMillis(struct timeval time_now)
{
    gettimeofday(&time_now, nullptr);
    return (uint64_t)(time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}

void GUI::ui(void)
{
    new_t = getMillis(time_now);
    if (new_t != t)
    {
        t = new_t;
        if (t - init == i * step + step)
        {
            i++;
            show();
        }
    }

    if (t - init >= interval)
    {
        init = getMillis(time_now);
        i = 0;
    }
}

void GUI::show(void)
{
    //system("clear");
    std::cout << i << "\n"; // sum(5.4f, 7.2f) << "\n";
}

GUI::GUI(/* args */)
{
    time_now = {};
    interval = 1000;
    fps = 20;
    step = interval / fps;
    i = 0;
}

GUI::~GUI()
{
}