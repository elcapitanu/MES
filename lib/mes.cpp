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

    UA_Client *client = UA_Client_new();
    UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    
    UA_StatusCode  retval = UA_Client_connect(client, "opc.tcp://localhost:4840");

    if(retval != UA_STATUSCODE_GOOD) {
        UA_Client_delete(client);
        return EXIT_FAILURE;
    }
    
    /* UA_Int32 value = 0;
    printf("\nReading the value of node (4, \"|var|CODESYS Control Win V3 x64.Application.POU.int_var\"):\n");
    UA_Variant *val = UA_Variant_new();
    retval = UA_Client_readValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.POU.int_var"), val);
    printf("the value is: %i\n", *(UA_Int32*)val->data);
    if(retval == UA_STATUSCODE_GOOD && UA_Variant_isScalar(val)) {
            value = *(UA_Int32*)val->data;
    }
    UA_Variant_delete(val); */


    UA_Boolean v = true;
    UA_Variant *myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &v, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.M1"), myVariant);
    UA_Variant_delete(myVariant);

    UA_Int16 value = 6;
    myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT16]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.P"), myVariant);
    UA_Variant_delete(myVariant);

    value = 0;
    myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &value, &UA_TYPES[UA_TYPES_INT16]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.rot1"), myVariant);
    UA_Variant_delete(myVariant);

    UA_Int64 valuet = 30000;
    myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &valuet, &UA_TYPES[UA_TYPES_INT64]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.timer1"), myVariant);
    UA_Variant_delete(myVariant);

    myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &v, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.ST2_rot"), myVariant);
    UA_Variant_delete(myVariant);

    myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &v, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.ST6_rot"), myVariant);
    UA_Variant_delete(myVariant);

    myVariant = UA_Variant_new();
    UA_Variant_setScalarCopy(myVariant, &v, &UA_TYPES[UA_TYPES_BOOLEAN]);
    UA_Client_writeValueAttribute(client, UA_NODEID_STRING(4, "|var|CODESYS Control Win V3 x64.Application.OPC.Start"), myVariant);
    UA_Variant_delete(myVariant);
 
    return 1;

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