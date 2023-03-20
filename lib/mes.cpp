#include "mes.hpp"

#include "opc-ua.cpp"

using namespace MES;

Socket::Socket()
{
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