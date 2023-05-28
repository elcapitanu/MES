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
        // strcpy(soc->message, db.getMESmessage(&day));
        if (soc->message != NULL)
        {
            soc->newMessage = true;
            day--;
        }
    }

    while (!stopRequested())
    {
        sleep(0.001);
        cout;
        if (soc->newMessage)
        {
            day++;
            state = 0;
            totaldeliv = 0;
            isToActuate = true;

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

    for (int i = 0; i < 7; i++)
        plan.work[i] = 0;
    for (int i = 0; i < 9; i++)
        plan.deliver[i] = 0;
    for (int i = 0; i < 2; i++)
        plan.buy[i] = 0;

    while (m[pos++] != 'W')
        ;

    while (m[pos] != 'B')
    {
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

void MES::savePieceWarehouse()
{
    fac.remSpaceWar--;
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
                if (plan.deliver[state - 1] > 0)
                {
                    op.deliverPiece(state);
                    fac.p[state - 1]--;
                    plan.remOrders--;
                }
            }
            else if (state > 9 && state < 17) // work
            {
                cout << "ola\n";

                // verificar se ha pecas no armazem
                if (plan.work[state - 1 - 9] > 0)
                {
                    maq = chooseMachine(state - 9 + 2);
                    op.workPiece(chooseStart(state - 9 + 2), state - 9 + 2, maq);
                    plan.remOrders--;
                    fac.p[chooseStart(state - 9 + 2) - 1]--;
                    fac.p[state - 9 + 2 - 1]++;
                    fac.machines[maq - 1].operatedPieces[state - 9 + 2 - 1]++;
                    fac.machines[maq - 1].totalOperatedPieces++;
                    fac.machines[maq - 1].totalOperatingTime += op.time4piece(state - 9 + 2);
                    fac.machines[maq - 1].free = 0;
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
        else if (state > 9 && state < 17)
        {
            if (plan.work[state - 1 - 9] == 0 && fac.sensors[33])
            {
                state++;
                isToActuate = true;
            }
            else if (RE_OkP)
            {
                isToActuate = true;
                plan.work[state - 1 - 9]--;
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

    if (plan.tool[2 - 1] == toolNeed(final) && fac.machines[2 - 1].free)
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
    if (FE_M1)
        fac.machines[1 - 1].free = 1;
    if (FE_M2)
        fac.machines[2 - 1].free = 1;
    if (FE_M3)
        fac.machines[3 - 1].free = 1;
    if (FE_M4)
        fac.machines[4 - 1].free = 1;
}

void MES::updateMessage()
{
    int pos = 0;
    while (msg[pos++] != 'W')
        ;

    while (msg[pos] != 'B')
    {
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