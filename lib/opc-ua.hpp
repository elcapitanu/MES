#ifndef OPCAUA_HPP
#define OPCAUA_HPP

#include "../main.hpp"

#include "threads/Mthread.hpp"

#include <open62541/client_config_default.h>
#include <open62541/client_highlevel.h>
#include <open62541/client_subscriptions.h>
#include <open62541/plugin/log_stdout.h>

class OpcUa : public Tasks::Thread
{
public:
    OpcUa()
    {
#if DEBUG_THR
        cout << "OpcUa: ola" << endl;
#endif
    }

    ~OpcUa();

    void workPiece(int start, int final, int machine);
    void deliverPiece(int type);
    void changeTool(int machine, int newTool);
    void readSensors(bool *sensors);


private:
    inline std::string getName() override
    {
        return "OPCUA";
    }

    void onMain() override;

    UA_Client *client;

    int OpcUaConnect();
    // void OpcUaWriteVariable();
    bool OpcUaReadVariableBool(int nodeid, char *stringid);
    int OpcUaReadVariableInt16(int nodeid, char *stringid);
    int OpcUaReadVariableInt32(int nodeid, char *stringid);
    int OpcUaReadVariableInt64(int nodeid, char *stringid);
    void OpcUaWriteVariableBool(int nodeid, char *stringid, bool value);
    void OpcUaWriteVariableInt16(int nodeid, char *stringid, u_int16_t value);
    void OpcUaWriteVariableInt32(int nodeid, char *stringid, u_int32_t value);
    void OpcUaWriteVariableInt64(int nodeid, char *stringid, u_int64_t value);

    int time4piece(int final);
};

#endif