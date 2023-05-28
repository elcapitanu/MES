#include "mes.hpp"

MES::~MES()
{
#if DEBUG_THR
    cout << "MES: adeus" << endl;
#endif
}

void MES::onMain()
{
#if DEBUG_THR
    cout << "MES: tou vivo" << endl;
#endif
    bool commsOK = isConnected2PLC() & isConnected2DB() & isConnected2ERP();
    while (!commsOK)
    {
        op.start();
        db.start();

        commsOK = isConnected2PLC() & isConnected2DB() & isConnected2ERP();

        if (stopRequested())
            break;
    }

    if (db.checkProgressWorking() == -1)
    {
        // read from db following commands to procede floor work
        fac.docks[0].totalUnloadedPieces = db.GetTableDelivery(1);
        fac.docks[1].totalUnloadedPieces = db.GetTableDelivery(2);

        db.GetTableMachine(1, &fac.machines[0].tool, &fac.machines[0].totalOperatingTime, fac.machines[0].operatedPieces);
        db.GetTableMachine(2, &fac.machines[1].tool, &fac.machines[1].totalOperatingTime, fac.machines[1].operatedPieces);
        db.GetTableMachine(3, &fac.machines[2].tool, &fac.machines[2].totalOperatingTime, fac.machines[2].operatedPieces);
        db.GetTableMachine(4, &fac.machines[3].tool, &fac.machines[3].totalOperatingTime, fac.machines[3].operatedPieces);

        db.GetTablePiece(fac.p);

        strcpy(soc->message, db.getMESmessage(&day));
        if (soc->message != NULL)
        {
            soc->newMessage = true;
            day--;
        }
    }

    while (!stopRequested())
    {
        sleep(0.001);
        cout << "";
        if (soc->newMessage)
        {
            day++;
            state = 0;
            totaldeliv = 0;
            isToActuate = true;
    	    maq = 0;
            next = false;
            aux = false;

            soc->newMessage = false;

            strcpy(msg, soc->message);
            parser(msg);

            db.saveMESmessage(msg, day, 1);
            op.startDay();
        }

        if (day)
        {
            op.readSensors(fac.sensors);

            risingEdges();

            updateMachinesStatus();

            sendOrder2PLC();

            updateState();

            updateMessage();

            db.saveMESmessage(msg, day, 0);
            
            int docksx[2] = {fac.docks[0].totalUnloadedPieces, fac.docks[1].totalUnloadedPieces };
            db.UpdateTableDelivery(docksx);
            db.UpdateTableMachine(1, fac.machines[0].tool, fac.machines[0].totalOperatingTime, fac.machines[0].operatedPieces);
            db.UpdateTableMachine(2, fac.machines[1].tool, fac.machines[1].totalOperatingTime, fac.machines[1].operatedPieces);
            db.UpdateTableMachine(3, fac.machines[2].tool, fac.machines[2].totalOperatingTime, fac.machines[2].operatedPieces);
            db.UpdateTableMachine(4, fac.machines[3].tool, fac.machines[3].totalOperatingTime, fac.machines[3].operatedPieces);
            db.UpdateTablePiece(fac.p);

            RE_S0 = RE_S11 = RE_S16 = RE_S17 = RE_S18 = RE_OkP = FE_M1 = FE_M2 = FE_M3 = FE_M4 = false;

            updateFactory();
        }
        sleep(0.01);
    }
}

void MES::parser(char *m)
{
    plan.totalOrders = 0;
    int pos = 1;

    for (int i = 0; i < 8; i++)
        plan.work[i] = 0;
    for (int i = 0; i < 9; i++)
        plan.deliver[i] = 0;
    for (int i = 0; i < 2; i++)
        plan.buy[i] = 0;

    while (m[pos++] != 'W')
        ;

    while (m[pos] != 'B')
    {
        if(m[pos] - '0' == 1)
            plan.work[7] = m[pos + 1] - '0';
        else
            plan.totalOrders += plan.work[m[pos] - '0' - 1 - 2] = m[pos + 1] - '0';
        pos += 2;
    }
    pos++;
    while (m[pos] != 'D')
    {
        fac.p[m[pos] - '0' - 1] += plan.buy[m[pos] - '0' - 1] = m[pos + 1] - '0';
        pos += 2;
    }
    pos++;
    while (m[pos] != 'M')
    {
        int amount = plan.deliver[m[pos] - '0' - 1] = m[pos + 1] - '0';
        totaldeliv += amount;
        plan.totalOrders += amount;
        pos += 2;
    }
    pos++;
    while (m[pos] != '*')
    {
        plan.tool[0] = m[pos] - '0';
        plan.tool[1] = m[pos + 1] - '0';
        plan.tool[2] = m[pos + 2] - '0';
        plan.tool[3] = m[pos + 3] - '0';
        pos += 4;
    }

    plan.remOrders = plan.totalOrders;

    return;
}

void MES::updateFactory()
{
    int totalPieces = 0;
    for (int i = 0; i < 9; i++)
        totalPieces += fac.p[i];

    for (int i = 0; i < 4; i++)
        fac.machines[i].tool = plan.tool[i];

    fac.docks[0].totalUnloadedPieces = op.OpcUaReadVariableInt16(4, (char*)"|var|CODESYS Control Win V3 x64.Application.OPC.dock1");
    fac.docks[1].totalUnloadedPieces = op.OpcUaReadVariableInt16(4, (char*)"|var|CODESYS Control Win V3 x64.Application.OPC.dock2");
    fac.remSpaceWar = 32 - op.OpcUaReadVariableInt16(4, (char*)"|var|CODESYS Control Win V3 x64.Application.OPC.arm");

    return;
}

void MES::addPiece(int type)
{
    fac.p[type - 1]++;
    fac.total++;
}

void MES::updateMachine(int machine, int newTool)
{
    fac.machines[machine - 1].tool = newTool;
}

void MES::sendOrder2PLC()
{
    if (op.connected)
    {
        if (isToActuate)
        {
            if (state == 0) // update tools
            {
                for (int machine = 1; machine < 5; machine++)
                    op.changeTool(machine, plan.tool[machine - 1]);

                op.startDelivery();
                if (totaldeliv == 0)
                    op.startWork();
            }
            else if (state > 0 && state < 10) // deliver
            {
                if (plan.deliver[state - 1] > 0 && fac.p[state - 1]>0)
                {
                    op.deliverPiece(state);
                    fac.p[state - 1]--;
                    plan.remOrders--;
                }
            }

            else if (state > 9 && state < 18) // work
            {

                if(state == 17){
                    if(plan.work[7] > 0 && fac.p[0]>0)
                    {
                        if (notSameSide(chooseMachine(6)))
                        {
                            maq = chooseMachine(6);
                            cout << "maq escolhida  " << maq << " status maq:" << maq << endl;
                            op.workPiece(1, 6, maq);
                            fac.machines[maq - 1].free = 0;
                            next = true;

                            plan.remOrders--;
                            fac.p[0]--;
                            fac.p[5]++;
                            fac.machines[maq - 1].operatedPieces[5]++;
                            fac.machines[maq - 1].totalOperatedPieces++;
                            fac.machines[maq - 1].totalOperatingTime += op.time4piece(6);
                            
                        }
                        else
                            next = false;
                    }
                }
                else
                {
                    if(plan.work[state - 1 - 9] > 0 && fac.p[chooseStart(state - 9 + 2) - 1]>0){
                        if (notSameSide(chooseMachine(state - 9 + 2)))
                        {
                            maq = chooseMachine(state - 9 + 2);
                            cout << "maq escolhida  " << maq << " status maq:" << maq << endl;
                            op.workPiece(chooseStart(state - 9 + 2), state - 9 + 2, maq);
                            fac.machines[maq - 1].free = 0;
                            next = true;

                            plan.remOrders--;
                            fac.p[chooseStart(state - 9 + 2) - 1]--;
                            fac.p[state - 9 + 2 - 1]++;
                            fac.machines[maq - 1].operatedPieces[state - 9 + 2 - 1]++;
                            fac.machines[maq - 1].totalOperatedPieces++;
                            fac.machines[maq - 1].totalOperatingTime += op.time4piece(state - 9 + 2);
                            
                        }
                        else
                            next = false;
                    }
                }
            }
            isToActuate = false;
        }
    }
}

void MES::updateState()
{
    if (op.connected)
    {
        if (state == 0)
        {
            state = 1;
            isToActuate = true;
        }
        else if (state > 0 && state < 10)
        {
            if (RE_S0 && totaldeliv > 0)
            {
                isToActuate = true;
                plan.deliver[state - 1]--;
                totaldeliv--;
            }
            if (totaldeliv == 0 && fac.sensors[34])
            {

                state = 10;
                isToActuate = true;
            }
            else if (plan.deliver[state - 1] == 0 && totaldeliv > 0)
            {
                state++;
                isToActuate = true;
            }
        }
        else if (state > 9 && state < 18)
        {
            if(state == 17)
            {
                if (plan.work[7] == 0)
                {
                    state++;
                    isToActuate = true;
                    aux = false;
                }
                else if (plan.work[7]!=0 && RE_OkP && next)
                {
                    isToActuate = true;
                    plan.work[7]--;
                    aux = false;
                    next = false;
                }
                else if(!next){
                    isToActuate = true;
                }
            }
            else
            {
                if (plan.work[state - 1 - 9] == 0)
                {
                    state++;
                    isToActuate = true;
                    aux = false;
                }
                else if (plan.work[state - 1 - 9]!=0 && RE_OkP && next)
                {
                    isToActuate = true;
                    plan.work[state - 1 - 9]--;
                    aux = false;
                    next = false;
                }
                else if(!next){
                    isToActuate = true;
                }
            }
        }
    }
}

int MES::toolNeed(int final)
{
    switch (final)
    {
    case 3:
        return 2;
    case 4:
        return 3;
    case 5:
        return 4;
    case 6:
        return 1;
    case 7:
        return 4;
    case 8:
        return 3;
    case 9:
        return 3;
    }
    return -1;
}

int MES::chooseMachine(int final)
{

    if (plan.tool[2 - 1] == toolNeed(final) && fac.machines[2 - 1].free && fac.machines[1 - 1].free)
        return 2;
    else if (plan.tool[4 - 1] == toolNeed(final) && fac.machines[4 - 1].free)
        return 4;
    else if (plan.tool[3 - 1] == toolNeed(final) && fac.machines[3 - 1].free)
        return 3;
    else if (plan.tool[1 - 1] == toolNeed(final) && fac.machines[1 - 1].free)
        return 1;
    else if (plan.tool[2 - 1] == toolNeed(final))
        return 2;
    else if (plan.tool[4 - 1] == toolNeed(final))
        return 4;
    else if (plan.tool[3 - 1] == toolNeed(final))
        return 3;
    else if (plan.tool[1 - 1] == toolNeed(final))
        return 1;

    return -1;
}

int MES::chooseStart(int final)
{
    switch (final)
    {
    case 1:
        return 1;
    case 3:
        return 2;
    case 4:
        return 2;
    case 5:
        return 9;
    case 6:
        return 3;
    case 7:
        return 4;
    case 8:
        return 6;
    case 9:
        return 7;
    default:
        break;
    }

    return -1;
}

int MES::machineTransition(int machine)
{
    switch (machine)
    {
    case 1:
        return RE_S11;
    case 2:
        return RE_S18;
    case 3:
        return RE_S16;
    case 4:
        return RE_S17;
    }

    return -1;
}

void MES::risingEdges()
{

    if (!previous_S0 && fac.sensors[0])
    {
        RE_S0 = true;
    }
    if (!previous_S11 && fac.sensors[11])
    {
        RE_S11 = true;
    }
    if (!previous_S16 && fac.sensors[16])
    {
        RE_S16 = true;
    }
    if (!previous_S17 && fac.sensors[17])
    {
        RE_S17 = true;
    }
    if (!previous_S18 && fac.sensors[18])
    {
        RE_S18 = true;
    }
    if (!previous_OkP && fac.sensors[33])
    {
        RE_OkP = true;
        aux = true;
    }
    if (previous_M1 && !fac.sensors[11])
    {
        FE_M1 = true;
    }
    if (previous_M2 && !fac.sensors[18])
    {
        FE_M2 = true;
    }
    if (previous_M3 && !fac.sensors[16])
    {
        FE_M3 = true;
    }
    if (previous_M4 && !fac.sensors[17])
    {
        FE_M4 = true;
    }

    previous_S0 = fac.sensors[0];
    previous_S11 = fac.sensors[11];
    previous_S16 = fac.sensors[16];
    previous_S17 = fac.sensors[17];
    previous_S18 = fac.sensors[18];
    previous_M1 = fac.sensors[11];
    previous_M2 = fac.sensors[18];
    previous_M3 = fac.sensors[16];
    previous_M4 = fac.sensors[17];
    previous_OkP = fac.sensors[33];
}

void MES::updateMachinesStatus()
{
    int time;
    if (FE_M1)
    {
        fac.machines[1 - 1].free = 1;
        time = op.OpcUaReadVariableInt64(4, (char*)"|var|CODESYS Control Win V3 x64.Application.GVL.duration_M1");
        sendTotalProductionTime2ERP(machpiece[0], time);
        machpiece[0] = 0;
    }
    if (FE_M2)
    {
        fac.machines[2 - 1].free = 1;
        time = op.OpcUaReadVariableInt64(4, (char*)"|var|CODESYS Control Win V3 x64.Application.GVL.duration_M2");
        sendTotalProductionTime2ERP(machpiece[1], time);
        machpiece[1] = 0;
    }
    if (FE_M3)
    {
        fac.machines[3 - 1].free = 1;
        time = op.OpcUaReadVariableInt64(4, (char*)"|var|CODESYS Control Win V3 x64.Application.GVL.duration_M3");
        sendTotalProductionTime2ERP(machpiece[2], time);
        machpiece[2] = 0;
    }
    if (FE_M4)
    {
        fac.machines[4 - 1].free = 1;
        time = op.OpcUaReadVariableInt64(4, (char*)"|var|CODESYS Control Win V3 x64.Application.GVL.duration_M4");
        sendTotalProductionTime2ERP(machpiece[3], time);
        machpiece[3] = 0;
    }

}

void MES::updateMessage()
{
    int pos = 0;
    while (msg[pos++] != 'W')
        ;

    while (msg[pos] != 'B')
    {
        if(msg[pos] - '0' == 1)
            msg[pos + 1] = char(plan.work[7]) + '0';
        else
            msg[pos + 1] = char(plan.work[msg[pos] - '0' - 1 - 2]) + '0';
        pos += 2;
    }
    pos++;
    while (msg[pos] != 'D')
    {
        msg[pos + 1] = char(plan.buy[msg[pos] - '0' - 1]) + '0';
        pos += 2;
    }
    pos++;
    while (msg[pos] != 'M')
    {
        msg[pos + 1] = char(plan.deliver[msg[pos] - '0' - 1]) + '0';
        pos += 2;
    }
}

bool MES::isConnected2ERP()
{
    return soc->isConnected();
}

bool MES::isConnected2PLC()
{
    return op.connected;
}

bool MES::isConnected2DB()
{
    return db.connected;
}


bool MES::notSameSide(int next)
{

    switch(next)
    {
        case 1:
            if(maq == 2 && !fac.sensors[18])
                return false;
            else
                return true;
        case 2:
            if(maq == 1 && !fac.sensors[11])
                return false;
            else
                return true;
        case 3:
            if(maq == 4 && !fac.sensors[17])
                return false;
            else
                return true;
        case 4:
            if(maq == 3 && !fac.sensors[16])
                return false;
            else
                return true;
    } 

    return false;
}

void MES::sendTotalProductionTime2ERP(int type, int time)
{
    char message[128];
    sprintf(message, "@P%d,%d,*", type,time);
    soc->sendMessage(message);
}