#include "mes.hpp"

using namespace MES;

Socket::Socket()
{
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

static volatile UA_Boolean running = true;

int OpcUa::OpcUa_Connect()
{
    
    UA_Server *server = UA_Server_new();

    UA_ServerConfig_setDefault(UA_Server_getConfig(server));

    UA_StatusCode retval = UA_Server_run(server, &running);

    UA_Server_delete(server);
    return retval == UA_STATUSCODE_GOOD ? EXIT_SUCCESS : EXIT_FAILURE;
}

Database::Database()
{
}

Database::~Database()
{
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