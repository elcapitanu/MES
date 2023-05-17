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
        }
    }
}

int MES::type2pos(char *type)
{
    if (!strcmp(type, "p1"))
        return 0;
    else if (!strcmp(type, "p2"))
        return 1;
    else if (!strcmp(type, "p3"))
        return 2;
    else if (!strcmp(type, "p4"))
        return 3;
    else if (!strcmp(type, "p5"))
        return 4;
    else if (!strcmp(type, "p6"))
        return 5;
    else if (!strcmp(type, "p7"))
        return 6;
    else if (!strcmp(type, "p8"))
        return 7;
    else if (!strcmp(type, "p9"))
        return 8;
    else if (!strcmp(type, "e1"))
        return 9;
    else if (!strcmp(type, "e2"))
        return 10;
    else if (!strcmp(type, "e3"))
        return 11;
    else if (!strcmp(type, "e4"))
        return 12;
    else if (!strcmp(type, "e5"))
        return 13;
    else if (!strcmp(type, "e6"))
        return 14;
    else if (!strcmp(type, "e7"))
        return 15;
    else if (!strcmp(type, "e8"))
        return 16;
    else if (!strcmp(type, "e9"))
        return 17;

    return -1;
}

int MES::parser(char *m)
{
    char *token = strtok(msg, ",");

    if (strcmp(token, "start"))
        newDay = 0;
    else
    {
        newDay = 1;
        orders = 0;
    }

    while (newDay)
    {
        token = strtok(NULL, ",");

        if (!strcmp(token, "*") || token == NULL)
            break;

        int pos = type2pos(token);

        if (pos < 0 || pos > 17)
            break;

        orders += order[pos] = atoi(strtok(NULL, ","));
    }

    return newDay;
}

void MES::planDay()
{
    day++;
    newDay = 0;
    ordersLeft = orders;

    return;
}