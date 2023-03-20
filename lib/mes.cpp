#include "mes.hpp"

#include "opc-ua.cpp"

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
    client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
}

OpcUa::~OpcUa()
{
    UA_Client_delete(client);
}

static volatile UA_Boolean running = true;

int OpcUa::OpcUaConnect()
{
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (retval != UA_STATUSCODE_GOOD)
    {
        return -1;
    }

    return 1;
}

bool OpcUa::OpcUaReadVariableBool(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
    {
        return *(UA_Boolean *)val->data;
    }
    UA_Variant_delete(val);
    return false;
}

int OpcUa::OpcUaReadVariableInt16(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
    {
        return *(UA_Int16 *)val->data;
    }
    UA_Variant_delete(val);

    return -1;
}

int OpcUa::OpcUaReadVariableInt32(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
    {
        return *(UA_Int32 *)val->data;
    }
    UA_Variant_delete(val);

    return -1;
}

int OpcUa::OpcUaReadVariableInt64(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
    {
        return *(UA_Int64 *)val->data;
    }
    UA_Variant_delete(val);

    return -1;
}

void OpcUa::OpcUaWriteVariableBool(int nodeid, char *stringid, bool value)
{
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), myVariant);
    UA_Variant_delete(myVariant);
}

void OpcUa::OpcUaWriteVariableInt16(int nodeid, char *stringid, u_int16_t value)
{
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT16]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), myVariant);
    UA_Variant_delete(myVariant);
}

void OpcUa::OpcUaWriteVariableInt32(int nodeid, char *stringid, u_int32_t value)
{
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT32]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), myVariant);
    UA_Variant_delete(myVariant);
}

void OpcUa::OpcUaWriteVariableInt64(int nodeid, char *stringid, u_int64_t value)
{
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT64]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), myVariant);
    UA_Variant_delete(myVariant);
}

Database::Database()
{
}

Database::~Database()
{
}


int Algorithm::connectToPLC(void)
{
    return op.OpcUaConnect();
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
    return soc.sendMessage(0);

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