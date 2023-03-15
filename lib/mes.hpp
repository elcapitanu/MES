#ifndef MES_HPP
#define MES_HPP

#include <stdint.h>

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