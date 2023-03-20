#ifndef MES_HPP
#define MES_HPP

#include <stdint.h>
#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>

#include <signal.h>
#include <stdlib.h>

namespace MES
{
    class Socket
    {
    private:
    public:
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
        Socket soc;
        Database db;
        OpcUa op;
    public:
        uint16_t orders;
        void addNumberOfOrders(uint16_t number);

        void connectToDatabase(void);

        void connectToERP(void);

        int connectToPLC(void);

        Algorithm();
        ~Algorithm();
    };
}

#endif