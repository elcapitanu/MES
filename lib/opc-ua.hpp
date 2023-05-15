#ifndef OPCAUA_HPP
#define OPCAUA_HPP

#include "../main.hpp"

#include "threads/Mthread.hpp"

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>

using std::cin;
using std::cout;
using std::endl;

class OpcUa : public Tasks::Thread
{
public:
    OpcUa()
    {
        cout << "OpcUa: ola" << endl;

        client = UA_Client_new();
        UA_ClientConfig_setDefault(UA_Client_getConfig(client));
    }

    ~OpcUa();

    int OpcUaConnect();
    void OpcUaWriteVariable();
    bool OpcUaReadVariableBool(int nodeid, char *stringid);
    int OpcUaReadVariableInt16(int nodeid, char *stringid);
    int OpcUaReadVariableInt32(int nodeid, char *stringid);
    int OpcUaReadVariableInt64(int nodeid, char *stringid);
    void OpcUaWriteVariableBool(int nodeid, char *stringid, bool value);
    void OpcUaWriteVariableInt16(int nodeid, char *stringid, u_int16_t value);
    void OpcUaWriteVariableInt32(int nodeid, char *stringid, u_int32_t value);
    void OpcUaWriteVariableInt64(int nodeid, char *stringid, u_int64_t value);

private:
    inline std::string getName() override
    {
        return "OPCUA";
    }

    void onMain() override;

    UA_Client *client;
};

#endif