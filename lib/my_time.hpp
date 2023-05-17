#ifndef MY_TIME_HPP
#define MY_TIME_HPP

#include "../main.hpp"

uint64_t initTime(struct timeval time_now);
uint64_t getMillis(struct timeval time_now);
int refresh(struct timeval time_now);

#endif