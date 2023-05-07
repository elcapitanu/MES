#ifndef TCP_HPP
#define TCP_HPP

#include <stdint.h>
#include <signal.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "threads/Mthread.hpp"

using std::cin;
using std::cout;
using std::endl;

class Socket : public Tasks::Thread
{
public:
    Socket()
    {
        cout << "SOCKET: ola" << endl;

        char *serverIp = "127.0.0.1";
        int port = 2223;
        // setup a socket and connection tools
        host = gethostbyname(serverIp);
        bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
        sendSockAddr.sin_family = AF_INET;
        sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
        sendSockAddr.sin_port = htons(port);
        clientSd = socket(AF_INET, SOCK_STREAM, 0);
    }

    ~Socket();

private:
    inline std::string getName() override
    {
        return "SOCKET";
    }

    void onMain() override;

    char message[100] = {};

    struct hostent *host;
    sockaddr_in sendSockAddr;
    int clientSd;
    int initConnection(void);
    int sendMessage(uint16_t orders);
    int receiveMessage(char *message);
};

#endif