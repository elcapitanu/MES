#ifndef TIME_HPP
#define TIME_HPP

#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>

void initTime(void);
uint64_t getMillis(struct timeval time_now);
int refresh(void);

#endif