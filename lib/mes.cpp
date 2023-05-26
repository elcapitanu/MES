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
    while (!op->connected)
        ;

    while (!stopRequested())
    {
        if (soc->newMessage)
        {
            soc->newMessage = false;

            strcpy(msg, soc->message);

            parser(msg);

            state = 0;
            day++;
        }

        if (day)
        {
            op->readSensors(fac.sensors);

            sendOrder2PLC();

            updateState();

            updateFactory();
        }
    }
}

void MES::parser(char *m)
{
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
        plan.work[m[pos] - '0' - 1 - 2] = m[pos + 1] - '0';
        pos += 2;
    }
    pos++;
    while (m[pos] != 'D')
    {
        plan.buy[m[pos] - '0' - 1] = m[pos + 1] - '0';
        pos += 2;
    }
    pos++;
    while (m[pos] != 'M')
    {
        plan.deliver[m[pos] - '0' - 1] = m[pos + 1] - '0';
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

    return;
}

void MES::updateFactory()
{
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
    fac.remSpaceWar++;
}

void MES::sendOrder2PLC()
{
    if (isToActuate)
    {
        if (state == 0) // update tools
        {
            op->changeTool(1, plan.tool[0]);
            op->changeTool(2, plan.tool[1]);
            op->changeTool(3, plan.tool[2]);
            op->changeTool(4, plan.tool[3]);
        }
        else if (state > 0 && state < 10) // deliver
        {
            if (plan.deliver[state - 1] > 0)
                op->deliverPiece(state);
        }
        else if (state > 9 && state < 17) // work
        {
            maq = chooseMachine(state - 9 + 2);
            op->workPiece(chooseStart(state - 9 + 2), state - 9 + 2, maq);
            plan.work[state - 1 - 9 + 2]--;
        }
        isToActuate = false;
    }
}

void MES::updateState()
{
    if (state == 0)
    {
        state = 1;
        isToActuate = true;
    }
    else if (state > 0 && state < 10)
    {
        if (fac.sensors[0])
        {
            isToActuate = true;
            plan.deliver[state - 1]--;
            totaldeliv--;
        }
        if (totaldeliv == 0)
        {

            state = 10;
        }
        if (plan.deliver[state - 1] == 0)
        {
            state++;
        }
    }
    else if (state > 9 && state < 17)
    {
        if (fac.sensors[machineTransition(maq)])
        {
            isToActuate = true;
            plan.work[state - 1 - 9 + 2]--;
        }
        if (plan.work[state - 1 - 9 + 2] == 0)
        {
            state++;
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
    if (plan.tool[2 - 1] == toolNeed(final) && plan.tool[2 - 1])
        return 2;
    else if (plan.tool[4 - 1] == toolNeed(final) && plan.tool[4 - 1])
        return 4;
    else if (plan.tool[1 - 1] == toolNeed(final) && plan.tool[1 - 1])
        return 1;
    else if (plan.tool[3 - 1] == toolNeed(final) && plan.tool[3 - 1])
        return 3;
    else if (plan.tool[2 - 1] == toolNeed(final))
        return 2;
    else if (plan.tool[4 - 1] == toolNeed(final))
        return 4;
    else if (plan.tool[1 - 1] == toolNeed(final))
        return 1;
    else if (plan.tool[3 - 1] == toolNeed(final))
        return 3;

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
        return 11;
    case 2:
        return 18;
    case 3:
        return 16;
    case 4:
        return 17;
    }

    return -1;
}

/* int Database::connectDatabase()
{
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK){
        result = PQexec(dbconn, "SET search_path TO up201905660;");
        PQclear(result);
        result = PQexec(dbconn, "SHOW search_path;");
        PQclear(result);
        return 1;
    }
    else return 0;
}

int Database::checkProgressWorking()
{
    PGresult* result;
    std::string order;
    int dbStatus ; //get this value from database

    if (PQstatus(dbconn) == CONNECTION_OK){
        order = "SELECT status FROM requests;";
        result = PQexec(dbconn, order.c_str());
        dbStatus = atoi(PQgetvalue(result, 0, 0));
        PQclear(result);
    }

    if(status == -1 && dbStatus == 1){ //previously working
        return -1;
    }
    if(status == -1 && dbStatus == -1){ //start working
        status = 1;
        //write status on database
        PGresult* result;
        std::string order;
        if (PQstatus(dbconn) == CONNECTION_OK){
            order = "Update requests \n SET status = 1;";
            result = PQexec(dbconn, order.c_str());
            PQclear(result);
        }
        return 1;
    }
    if(status && dbStatus){//working with connection
        return 1;
    }

    return -1;
}

void Database::writeAlgorithm()
{

}

void Database::readAlgorithm()
{

}

Database::Database()
{
    status = -1;
}

Database::~Database()
{
    //write db status = -1
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK){
        order = "Update requests \n SET status = -1;";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);
    }
} */