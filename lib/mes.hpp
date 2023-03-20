#ifndef MES_HPP
#define MES_HPP

#include <stdint.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>

#include <signal.h>
#include <stdlib.h>

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
        UA_Client* client;
    public:
        OpcUa();
        ~OpcUa();
        int OpcUaConnect();
        void OpcUaWriteVariable();
        bool OpcUaReadVariableBool(int nodeid, char* stringid);
        int OpcUaReadVariableInt16(int nodeid, char* stringid);
        int OpcUaReadVariableInt32(int nodeid, char* stringid);
        int OpcUaReadVariableInt64(int nodeid, char* stringid);
        void OpcUaWriteVariableBool(int nodeid, char* stringid, bool value);
        void OpcUaWriteVariableInt16(int nodeid, char* stringid, u_int16_t value);
        void OpcUaWriteVariableInt32(int nodeid, char* stringid, u_int32_t value);
        void OpcUaWriteVariableInt64(int nodeid, char* stringid, u_int64_t value);
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
        OpcUa op;

        struct timeval time_now;

        uint64_t init_t;

        uint16_t orders;

        char message[100] = {};

        void addNumberOfOrders(uint16_t number);

        void connectToDatabase(void);

        int connectToERP(void);

        int connectToPLC(void);

        int sendValuesToERP(void);

        void sendValuesToPLC(void);

        int receiveValuesFromERP(void);

        void receiveValuesFromPLC(void);

        Algorithm();
        ~Algorithm();
    };
}

#endif