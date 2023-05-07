#include "tcp.hpp"

Socket::~Socket()
{
}

void Socket::onMain()
{
    cout << "SOCKET: tou vivo" << endl;

    while (initConnection() != 1)
        ;

    while (1)
    {
        receiveMessage(message);
    }
}

int Socket::initConnection(void)
{
    // try to connect...
    if (connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr)) < 0)
        return 0;

    cout << "Connected to ERP!" << endl;
    return 1;
}

int Socket::sendMessage(uint16_t orders)
{
    char msg[1500];
    memset(&msg, 0, sizeof(msg)); // clear the buffer
    sprintf(msg, "%hd", orders);
    return send(clientSd, (char *)&msg, strlen(msg), MSG_DONTWAIT);
}

int Socket::receiveMessage(char *message)
{
    char msg[1500];
    memset(&msg, 0, sizeof(msg)); // clear the buffer
    int bytesRead = recv(clientSd, (char *)&msg, sizeof(msg), MSG_DONTWAIT);
    if (bytesRead > 0)
        strcpy(message, msg);

    return 0;
}