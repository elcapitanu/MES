#ifndef MAIN_HPP
#define MAIN_HPP

#include <iostream>

#include <thread>
#include <mutex>
#include <unordered_map>
#include <condition_variable>
#include <cstring>
#include <functional>
#include <sys/socket.h>
#include <arpa/inet.h>

#define CLIENT_PORT		54321
#define MES_PORT		2223
#define BUFF_LEN		1024
#define DAY_DURATION  	5
//#define MES_ADDR    "XUXA"

#define DEBUG_THR		0
#define DEBUG_XML		0
#define DEBUG_LIST		0
#define DEBUG_ALLOC		0
#define DEBUG_PIPE		0
#define DISABLE_MPS		0

#endif