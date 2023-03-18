#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

uint64_t initTime(struct timeval time_now);
uint64_t getMillis(struct timeval time_now);
int refresh(struct timeval time_now);

#endif