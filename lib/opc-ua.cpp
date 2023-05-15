#include "opc-ua.hpp"

#define OPCUA_Start 0
#define OPCUA_P 1
#define OPCUA_ST2_rot 2
#define OPCUA_ST6_rot 3
#define OPCUA_PT2_rot 4
#define OPCUA_PT4_slide 5
#define OPCUA_PT7_slide 6
#define OPCUA_PT9_rot 7
#define OPCUA_MT2_rot 8
#define OPCUA_CT2_rot 9
#define OPCUA_MT6_rot 10
#define OPCUA_CT7_rot 11
#define OPCUA_M1 12
#define OPCUA_rot1 13
#define OPCUA_timer1 14
#define OPCUA_M2 15
#define OPCUA_rot2 16
#define OPCUA_timer2 17
#define OPCUA_M3 18
#define OPCUA_rot3 19
#define OPCUA_timer3 20
#define OPCUA_M4 21
#define OPCUA_rot4 22
#define OPCUA_timer4 23
#define OPCUA_Push 24

char OPCUA_VARIABLES[25][58] = {"|var|CODESYS Control Win V3 x64.Application.OPC.Start",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.P",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.ST2_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.ST6_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.PT2_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.PT4_slide",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.PT7_slide",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.PT9_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.MT2_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.CT2_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.MT6_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.CT7_rot",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M1",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.rot1",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer1",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M2",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.rot2",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer2",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M3",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.rot3",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer3",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M4",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.rot4",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer4",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.Push"};

OpcUa::~OpcUa()
{
    cout << "OpcUa: adeus" << endl;

    UA_Client_delete(client);
}

void OpcUa::onMain()
{
    cout << "OpcUa: tou vivo" << endl;

    while (1)
        ;
}

static volatile UA_Boolean running = true;

int OpcUa::OpcUaConnect()
{
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://192.168.56.1:4840");
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