#ifndef MES_HPP
#define MES_HPP

#include <stdint.h>
#include <open62541/plugin/log_stdout.h>
#include <open62541/server.h>
#include <open62541/server_config_default.h>

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
    public:
        OpcUa();
        ~OpcUa();
        int OpcUa_Connect();
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
    public:
        uint16_t orders;
        void addNumberOfOrders(uint16_t number);

        void connectToDatabase(void);

        void connectToERP(void);

        void connectToPLC(void);

        Algorithm();
        ~Algorithm();
    };
}

#endif