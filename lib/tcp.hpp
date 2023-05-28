#ifndef TCP_HPP
#define TCP_HPP

#include "../main.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#include "threads/Mthread.hpp"

class Socket : public Tasks::Thread
{
public:
    Socket()
    {
#if DEBUG_THR
        cout << "SOCKET: ola" << endl;
#endif
    }

    ~Socket();

    bool isConnected()
    {
        return connected;
    }

    bool newMessage;

    char message[1500] = {};

private:
    inline std::string getName() override
    {
        return "SOCKET";
    }

    void onMain() override;

    struct hostent *host;
    struct sockaddr_in servaddr;
    int clientSd;
    int initConnection(void);
    int sendMessage(uint16_t orders);
    int receiveMessage();

    bool connected;
};

#endif