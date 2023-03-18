#include "mes.hpp"

using std::cin;
using std::cout;
using std::endl;

using namespace MES;

int Socket::initConnection(void)
{
    // try to connect...
    if (connect(clientSd, (sockaddr *)&sendSockAddr, sizeof(sendSockAddr)) < 0)
        return 0;

    cout << "Connected with server!" << endl;
    return 1;
}

int Socket::sendMessage(uint16_t orders)
{
    char msg[1500];
    memset(&msg, 0, sizeof(msg)); // clear the buffer
    // strcpy(msg, "ola");
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

    /* message->erase();
    char msg[1500];
    memset(&msg, 0, sizeof(msg)); // clear the buffer
    int bytesRead = recv(clientSd, (char *)&msg, strlen(msg), MSG_DONTWAIT);

    // cout << msg << endl;
    if (bytesRead != -1)
        cout << msg << endl;
    // message->append(msg); */

    return 0;
}

Socket::Socket()
{
    char *serverIp = "127.0.0.1";
    int port = 8080;
    // setup a socket and connection tools
    host = gethostbyname(serverIp);
    bzero((char *)&sendSockAddr, sizeof(sendSockAddr));
    sendSockAddr.sin_family = AF_INET;
    sendSockAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr *)*host->h_addr_list));
    sendSockAddr.sin_port = htons(port);
    clientSd = socket(AF_INET, SOCK_STREAM, 0);
}

Socket::~Socket()
{
}

OpcUa::OpcUa()
{
}

OpcUa::~OpcUa()
{
}

Database::Database()
{
}

Database::~Database()
{
}

int Algorithm::connectToERP(void)
{
    while (getMillis(time_now) - init_t <= 10000)
    {
        if (refresh(time_now))
        {
            if (soc.initConnection() == 1)
                return 0;
        }
    }

    return -1;
}

int Algorithm::sendValuesToERP(void)
{
    if (orders % 100 == 0)
        return soc.sendMessage(orders);

    return 0;
}

int Algorithm::receiveValuesFromERP(void)
{
    return soc.receiveMessage(message);
}

void Algorithm::addNumberOfOrders(uint16_t number)
{
    orders += number;

    return;
}

Algorithm::Algorithm()
{
    orders = 0;
}

Algorithm::~Algorithm()
{
}