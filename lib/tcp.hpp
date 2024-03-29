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
        while ((clientSd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            ;

        bzero(&servaddr, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        servaddr.sin_port = htons(4321);

        connected = false;
        newMessage = false;
    }

    ~Socket();

    bool isConnected()
    {
        return connected;
    }
    int sendMessage(char *message);

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
    int receiveMessage();

    bool connected;
};

#endif