#include "tcp.hpp"

Socket::~Socket()
{
#if DEBUG_THR
    cout << "SOCKET: adeus" << endl;
#endif

    close(clientSd);
}

void Socket::onMain()
{
#if DEBUG_THR
    cout << "SOCKET: tou vivo" << endl;
#endif

    while (initConnection() != 0)
        ;

    connected = true;

    while (!stopRequested())
    {
        if (!connected)
            initConnection();

        if (receiveMessage())
        {
        }
    }
}

int Socket::initConnection(void)
{
    return connect(clientSd, (struct sockaddr *)&servaddr, sizeof(servaddr));
}

int Socket::sendMessage(uint16_t orders)
{
    char msg[1500];
    bzero(msg, sizeof(msg));
    sprintf(msg, "%hd", orders);
    return send(clientSd, (char *)&msg, strlen(msg), MSG_DONTWAIT);
}

int Socket::receiveMessage()
{
    char msg[1500];
    bzero(msg, sizeof(msg));
    int bytesRead = recv(clientSd, (char *)&msg, sizeof(msg), MSG_NOSIGNAL);

    // msg[strlen(msg) - 3] = '\0';

    if (bytesRead > 0)
    {
        strcpy(message, msg);
        newMessage = true;
    }
    else if (bytesRead <= 0)
        connected = false;

    return bytesRead;
}