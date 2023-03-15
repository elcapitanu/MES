#include "time.hpp"

struct timeval time_now;

uint64_t init, t, new_t, interval, fps, step, i;

void initTime(void)
{
    time_now = {};
    interval = 1000;
    fps = 20;
    step = interval / fps;

    init = getMillis(time_now);
    i = 0;

    t = 0;

    return;
}

uint64_t getMillis(struct timeval time_now)
{
    gettimeofday(&time_now, nullptr);
    return (uint64_t)(time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
}

int refresh(void)
{
    new_t = getMillis(time_now);
    if (new_t != t)
    {
        t = new_t;
        if (t - init == i * step + step)
        {
            i++;
            return 1;
        }
    }

    if (t - init >= interval)
    {
        init = getMillis(time_now);
        i = 0;
    }

    return 0;
}