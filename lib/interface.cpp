#include "interface.hpp"

using namespace Interface;

uint64_t GUI::getMillis(struct timeval time_now)
{
    gettimeofday(&time_now, nullptr);
    return (uint64_t)(time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}

void GUI::ui(Algorithm mes)
{
    new_t = getMillis(time_now);
    if (new_t != t)
    {
        t = new_t;
        if (t - init == i * step + step)
        {
            i++;
            show(mes);
        }
    }

    if (t - init >= interval)
    {
        init = getMillis(time_now);
        i = 0;
    }
}

void GUI::show(Algorithm mes)
{
    system("clear");
    time(&date);
    cout << "*********************MES**********************" << endl
              << endl
              << name << "      " << ctime(&date) << endl
              << endl
              << "Number of orders: " << mes.orders << endl
              << endl
              << "************Ainda não faço nada :)************" << endl;
}

GUI::GUI()
{
    time_now = {};
    interval = 1000;
    fps = 20;
    step = interval / fps;
    i = 0;
    name.append("Bernardo Gabriel");
}

GUI::~GUI()
{
}