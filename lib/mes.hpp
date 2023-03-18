#ifndef MES_HPP
#define MES_HPP

#include <stdint.h>

#include <iostream>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "time.hpp"

namespace MES
{
    class Socket
    {
    private:
        /* struct hostent *host;
        sockaddr_in sendSockAddr;
        int clientSd; */

    public:
        struct hostent *host;
        sockaddr_in sendSockAddr;
        int clientSd;
        int initConnection(void);
        int sendMessage(uint16_t orders);
        int receiveMessage(char *message);

        Socket();
        ~Socket();
    };

    class OpcUa
    {
    private:
    public:
        OpcUa();
        ~OpcUa();
    };

    class Database
    {
    private:
    public:
        Database();
        ~Database();
    };

    class Algorithm
    {
    private:
        Database db;

    public:
        Socket soc;

        uint16_t orders;

        char message[100] = {};

        void addNumberOfOrders(uint16_t number);

        void connectToDatabase(void);

        void connectToERP(void);

        void connectToPLC(void);

        int sendValuesToERP(void);

        void sendValuesToPLC(void);

        int receiveValuesFromERP(void);

        void receiveValuesFromPLC(void);

        Algorithm();
        ~Algorithm();
    };
}

#endif