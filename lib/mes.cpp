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
        op->readSensors(fac.sensors);

        for (int i = 0; i < 33; i++)
        {
            if (fac.sensors[i])
                cout << i << "\n";
        }

        /* if new message from ERP */
        /* parse message */
        /* if new day */
        /* calculate plan for the day */

        /* execute plan */
        /* while - until last order */
        /* send order to PLC*/
        /* while - until order completed */
        /* send feedback to ERP */

        if (soc->newMessage) /* if new message from ERP */
        {
            soc->newMessage = false;

            strcpy(msg, soc->message);

            if (parser(msg) /* parse message */) /* if new day */
            {
                planDay(); /* calculate plan for the day */
            }
        }

        /* execute plan */
        if (day && ordersLeft) /* while - until last order */
        {
            /* send order to PLC*/
            /* while - until order completed */
            /* send feedback to ERP */

            /* go throught plc orders FIFO */
            /* send order to PLC */
            /* if order completed send next order */
        }

        updateFactory();
    }
}

int MES::parser(char *m)
{
    newDay = 1;
    orders = 0;

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
        fac.machines[0].tool = m[pos] - '0';
        fac.machines[1].tool = m[pos + 1] - '0';
        fac.machines[2].tool = m[pos + 2] - '0';
        fac.machines[3].tool = m[pos + 3] - '0';
        pos += 4;
    }

    return 0;
}

void MES::planDay()
{
    day++;
    newDay = 0;
    ordersLeft = orders;

    /* creates a FIFO with orders to PLC for the day */

    /* for (int i = 0; i < 9; i++)
        cout << "W" << i + 1 << " : " << plan.work[i] << endl;
    for (int i = 0; i < 9; i++)
        cout << "D" << i + 1 << " : " << plan.deliver[i] << endl;
    for (int i = 0; i < 2; i++)
        cout << "B" << i + 1 << " : " << plan.buy[i] << endl; */

    for (int type = 1; type < 10; type++)
    {
        while (plan.deliver[type - 1]-- > 0)
            op->deliverPiece(type);
    }

    for (int final = 1; final < 10; final++)
    {
        if (plan.work[final - 1] > 0)
        {
            int start;
            int machine;
            int tool;

            switch (final)
            {
            case 3:
                start = 2;
                tool = 2;
                break;
            case 4:
                start = 2;
                tool = 3;
                break;
            case 5:
                start = 9;
                tool = 4;
                break;
            case 6:
                start = 3;
                tool = 1;
                break;
            case 7:
                start = 4;
                tool = 4;
                break;
            case 8:
                start = 6;
                tool = 3;
                break;
            case 9:
                start = 7;
                tool = 3;
                break;

            default:
                break;
            }

            for (machine = 0; machine < 4; machine++)
            {
                if (fac.machines[machine].tool == tool)
                {
                    op->workPiece(start, final, machine + 1);
                    break;
                }
            }

            switch (tool)
            {
            case 1:
                op->changeTool(1, tool);
                break;
            case 2:
                op->changeTool(1, tool);
                break;
            case 3:
                op->changeTool(1, tool);
                break;
            case 4:
                op->changeTool(2, tool);
                break;

            default:
                break;
            }

            op->workPiece(start, final, machine);
        }
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