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
#define OPCUA_T1 13
#define OPCUA_timer1 14
#define OPCUA_M2 15
#define OPCUA_T2 16
#define OPCUA_timer2 17
#define OPCUA_M3 18
#define OPCUA_T3 19
#define OPCUA_timer3 20
#define OPCUA_M4 21
#define OPCUA_T4 22
#define OPCUA_timer4 23
#define OPCUA_Push 24
#define OPCUA_M 25
#define OPCUA_Timer 26

char OPCUA_VARIABLES[27][58] = {"|var|CODESYS Control Win V3 x64.Application.OPC.Start",
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
                                "|var|CODESYS Control Win V3 x64.Application.OPC.T1",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer1",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M2",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.T2",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer2",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M3",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.T3",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer3",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M4",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.T4",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer4",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.Push",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.M",
                                "|var|CODESYS Control Win V3 x64.Application.OPC.timer"};

#define OPCUA_AT1s0 0
#define OPCUA_ST1s0 1
#define OPCUA_ST2s0 2
#define OPCUA_PT1s0 3
#define OPCUA_PT2s0 4
#define OPCUA_PT3s0 5
#define OPCUA_MT1s0 6
#define OPCUA_MT2s0 7
#define OPCUA_CT1s0 8
#define OPCUA_CT2s0 9
#define OPCUA_CT3s0 10
#define OPCUA_ST3s0 11
#define OPCUA_PT4s0 12
#define OPCUA_MT3s0 13
#define OPCUA_CT4s0 14
#define OPCUA_ST4s0 15
#define OPCUA_PT5s0 16
#define OPCUA_PT6s0 17
#define OPCUA_ST5s0 18
#define OPCUA_PT7s0 19
#define OPCUA_MT4s0 20
#define OPCUA_CT5s0 21
#define OPCUA_AT2s0 22
#define OPCUA_ST7s0 23
#define OPCUA_ST6s0 24
#define OPCUA_PT8s0 25
#define OPCUA_PT9s0 26
#define OPCUA_PT10s0 27
#define OPCUA_MT5s0 28
#define OPCUA_MT6s0 29
#define OPCUA_CT6s0 30
#define OPCUA_CT7s0 31
#define OPCUA_CT8s0 32
#define OPCUA_OkProd 33
#define OPCUA_EndDel 34

char OPCUA_SENSORS[35][58] = {"|var|CODESYS Control Win V3 x64.Application.GVL.AT1s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST1s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST2s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT1s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT2s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT3s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.MT1s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.MT2s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT1s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT2s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT3s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST3s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT4s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.MT3s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT4s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST4s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT5s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT6s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST5s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT7s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.MT4s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT5s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.AT2s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST7s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.ST6s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT8s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT9s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.PT10s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.MT5s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.MT6s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT6s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT7s0",
                              "|var|CODESYS Control Win V3 x64.Application.GVL.CT8s0",
                              "|var|CODESYS Control Win V3 x64.Application.OPC.Ok_prod",
                              "|var|CODESYS Control Win V3 x64.Application.OPC.end_delv"};

OpcUa::~OpcUa()
{
#if DEBUG_THR
    cout << "OpcUa: adeus" << endl;
#endif
}

void OpcUa::start()
{
    client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));

    if (OpcUaConnect())
        connected = true;
}

void OpcUa::stop()
{
    UA_Client_delete(client);
}
static volatile UA_Boolean running = true;

int OpcUa::OpcUaConnect()
{
    UA_StatusCode retval = UA_Client_connect(client, "opc.tcp://localhost:4840");
    if (retval != UA_STATUSCODE_GOOD)
        return -1;

    return 1;
}

bool OpcUa::OpcUaReadVariableBool(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
        return *(UA_Boolean *)val->data;

    UA_Variant_delete(val);
    return false;
}

int OpcUa::OpcUaReadVariableInt16(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
        return *(UA_Int16 *)val->data;

    UA_Variant_delete(val);

    return -1;
}

int OpcUa::OpcUaReadVariableInt32(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
        return *(UA_Int32 *)val->data;

    UA_Variant_delete(val);

    return -1;
}

int OpcUa::OpcUaReadVariableInt64(int nodeid, char *stringid)
{
    UA_Variant *val = UA_Variant_new();
    UA_StatusCode retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(nodeid, stringid), val);

    if (retval == UA_STATUSCODE_GOOD)
        return *(UA_Int64 *)val->data;

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

int OpcUa::time4piece(int final)
{
    if (final == 3 || final == 4 || final == 7 || final == 9)
        return 10000;
    else if (final == 5)
        return 15000;
    else if (final == 6)
        return 20000;
    else if (final == 8)
        return 30000;

    return -1;
}

void OpcUa::workPiece(int start, int final, int machine)
{
    int timer = time4piece(final);

    if (machine == 1)
    {
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_Start], true);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_M], machine);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_P], start);
        OpcUaWriteVariableInt64(4, OPCUA_VARIABLES[OPCUA_Timer], timer);
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_ST2_rot], true);
    }
    else if (machine == 2)
    {
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_Start], true);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_M], machine);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_P], start);
        OpcUaWriteVariableInt64(4, OPCUA_VARIABLES[OPCUA_Timer], timer);
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_ST2_rot], true);
    }
    else if (machine == 3)
    {
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_Start], true);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_M], machine);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_P], start);
        OpcUaWriteVariableInt64(4, OPCUA_VARIABLES[OPCUA_Timer], timer);
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_PT2_rot], true);
    }
    else if (machine == 4)
    {
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_Start], true);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_M], machine);
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_P], start);
        OpcUaWriteVariableInt64(4, OPCUA_VARIABLES[OPCUA_Timer], timer);
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_PT2_rot], true);
        // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_PT4_slide], true);
    }

    return;
}

void OpcUa::deliverPiece(int type)
{
    // OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_Start], true);
    OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_P], type);
    OpcUaWriteVariableBool(4, OPCUA_VARIABLES[OPCUA_Push], true);

    return;
}

void OpcUa::changeTool(int machine, int newTool)
{
    if (machine == 1)
    {
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_T1], newTool);
    }
    else if (machine == 2)
    {
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_T2], newTool);
    }
    else if (machine == 3)
    {
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_T3], newTool);
    }
    else if (machine == 4)
    {
        OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_T4], newTool);
    }

    return;
}

void OpcUa::readSensors(bool *sensors)
{
    for (int i = 0; i < 35; i++)
        sensors[i] = OpcUaReadVariableBool(4, OPCUA_SENSORS[i]);

    return;
}

// reset sinais
void OpcUa::startDay()
{
    OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_M], 5);
}

void OpcUa::startWork()
{
    OpcUaWriteVariableBool(4, OPCUA_SENSORS[OPCUA_EndDel], true);
}

void OpcUa::startDelivery()
{
    OpcUaWriteVariableInt16(4, OPCUA_VARIABLES[OPCUA_M], 0);
}