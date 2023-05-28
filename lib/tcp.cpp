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

    cout << "connected bogays" << endl;
    connected = true;

    while (!stopRequested())
    {
        if (!connected)
            initConnection();

        if (receiveMessage())
        {
        }
    }
    sleep(0.01);
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
    // change MSG_NOSIGNAL to MSG_DONTWAIT
    // then need to change the way MES checks if lost connection to ERP - if then there is no way to check if lost connection, keep MSG_NOSIGNAL

    // msg[strlen(msg) - 3] = '\0';

    if (bytesRead > 0)
    {
        strcpy(message, msg);

        if (msg[0] == '@')
            newMessage = true;
    }
    else if (bytesRead <= 0)
        connected = false;

    return bytesRead;
}