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

    while (!stopRequested())
    {
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
    int multiplier = 0;

    while (1)
    {
        if (m[pos] == '*')
            break;

        switch (m[pos++])
        {
        case 'W':
            multiplier = 0;
            break;
        case 'D':
            multiplier = 1;
            break;
        case 'B':
            multiplier = 2;
            break;
        default:
            break;
        }

        int type = m[pos++];
        int quantity = m[pos++];

        orders += order[multiplier * 9 + type - '0' - 1] = quantity - '0';
    }

    return newDay;
}

void MES::planDay()
{
    day++;
    newDay = 0;
    ordersLeft = orders;

    /* creates a FIFO with orders to PLC for the day */

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