#include "interface.hpp"

GUI::~GUI()
{
#if DEBUG_THR
    cout << "GUI: adeus" << endl;
#endif
}

void GUI::onMain()
{
#if DEBUG_THR
    cout << "GUI: tou vivo" << endl;
#endif

    display.state = 0;

    while (!stopRequested())
    {
        if (refresh(messi->time_now) /* && if state is not a state to input long text */)
        {
            show();
        }

        if (display.state == 0)
        {
            if (*input == 'a')
                display.state = 1;
            else if (*input == 'b')
                display.state = 2;
            else if (*input == 'c')
                display.state = 3;
        }
        else if (display.state == 1)
        {
            if (*input == 'q')
                display.state = 0;
        }
        else if (display.state == 2)
        {
            if (*input == 'q')
                display.state = 0;
        }
        else if (display.state == 3)
        {
            if (*input == 'q')
                display.state = 0;
        }
    }
}

void GUI::show()
{
    system("clear");
    time(&date);
    if (display.state == 0)
    {
        cout << "\033[7;32m*********************Menu**********************\033[0m" << endl
             << endl
             << "a. MES1" << endl
             << "b. MES2" << endl
             << "c. Show factory" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;32m***********************************************\033[0m" << endl
             << endl
             << "          \033[7;37m" << ctime(&date) << "\033[0m" << endl;

        if (!soc->isConnected())
        {
            cout << "            \033[5;31mNot connected to ERP\033[0m" << endl
                 << endl;
        }

        cout << "\033[7;32m***********************************************\033[0m" << endl;
    }
    else if (display.state == 1)
    {
        cout << "\033[7;31m*********************MES1**********************\033[0m" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl;

        if (messi->day > 0)
        {
            cout << "Day: " << messi->day << endl
                 << endl
                 << "Number of orders: " << messi->orders << endl
                 << endl;
        }
        cout << "\033[7;31m***********************************************\033[0m" << endl
             << "Server: " << soc->message << endl
             << "\033[7;31m************Ainda não faço nada :)*************\033[0m" << endl;

        cout << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;31m***********************************************\033[0m" << endl;
    }
    else if (display.state == 2)
    {
        cout << "\033[7;33m*********************MES2**********************\033[0m" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl;
        if (messi->day > 0)
        {
            cout << "Day: " << messi->day << endl
                 << endl
                 << "Number of orders: " << messi->orders << endl
                 << endl;
        }
        cout << "\033[7;33m***********************************************\033[0m" << endl
             << "Server: " << soc->message << endl
             << "\033[7;33m************Ainda não faço nada :)*************\033[0m" << endl;

        cout << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;33m***********************************************\033[0m" << endl;
    }
    else if (display.state == 3)
    {
        cout << "\033[7;36m*******************Factory*********************************\033[0m" << endl
             << endl
             << name << "                   " << ctime(&date) << endl
             << endl
             << "\033[7;36m***********************************************************\033[0m" << endl
             << endl;

        cout << "                        \033[7;37mDay: " << messi->day << "\033[0m" << endl
             << endl
             << "                     \033[7;37m            \033[0m" << endl
             << "                     \033[7;37m \033[0m          \033[7;37m \033[0m" << endl
             << "                     \033[7;37m            \033[0m" << endl
             << endl
             << "\033[7;36m***********************************************************\033[0m" << endl
             << endl;

        factory2map();

        cout << "| " << map.warehouse[8] << " \033[0m |   -------------------------------------------------   " << endl
             << "| " << map.warehouse[7] << " \033[0m |    " << map.pos[0] << "   " << map.pos[1] << "   " << map.pos[2] << "   " << map.pos[3] << "   " << map.pos[4] << "   " << map.pos[5] << "   " << map.pos[6] << "   " << map.pos[7] << "   " << map.pos[8] << "   " << map.pos[9] << "   " << map.pos[10] << "   " << map.pos[11] << "    " << endl
             << "| " << map.warehouse[6] << " \033[0m |   -------     ---          ---          ---     ---   " << endl
             << "| " << map.warehouse[5] << " \033[0m |          | " << map.pos[12] << " |   | " << map.pos[13] << " || " << map.pos[14] << " |   | " << map.pos[15] << " || " << map.pos[16] << " |   | " << map.pos[17] << " |      " << endl
             << "| " << map.warehouse[4] << " \033[0m |          | " << map.pos[18] << " |   | " << map.pos[19] << " || " << map.pos[20] << " |   | " << map.pos[21] << " || " << map.pos[22] << " |   |   |      " << endl
             << "| " << map.warehouse[3] << " \033[0m |          | " << map.pos[23] << " |   | " << map.pos[24] << " || " << map.pos[25] << " |   | " << map.pos[26] << " || " << map.pos[27] << " |   | " << map.pos[28] << " |      " << endl
             << "| " << map.warehouse[2] << " \033[0m |   -------     ---          ---          ---     ---   " << endl
             << "| " << map.warehouse[1] << " \033[0m |    " << map.pos[29] << "   " << map.pos[30] << "   " << map.pos[31] << "   " << map.pos[32] << "   " << map.pos[33] << "   " << map.pos[34] << "   " << map.pos[35] << "   " << map.pos[36] << "   " << map.pos[37] << "   " << map.pos[38] << "   " << map.pos[39] << "   " << map.pos[40] << "    " << endl
             << "| " << map.warehouse[0] << " \033[0m |   -------------------------------------------------   " << endl
             << endl;

        cout << "\033[7;36m***********************************************************\033[0m" << endl
             << endl
             << "          Remaining space in the warehouse: " << messi->fac.remSpaceWar << endl
             << endl
             << "       | P1: " << messi->fac.p[0] << " | P2: " << messi->fac.p[1] << " | P3: " << messi->fac.p[2] << " | P4: " << messi->fac.p[3] << " | P5: " << messi->fac.p[4] << " |" << endl
             << "           | P6: " << messi->fac.p[5] << " | P7: " << messi->fac.p[6] << " | P8: " << messi->fac.p[7] << " | P9: " << messi->fac.p[8] << " |" << endl
             << endl
             << "         | M1: T" << messi->fac.m[0] << " | M2: T" << messi->fac.m[1] << " | M3: T" << messi->fac.m[2] << " | M4: T" << messi->fac.m[3] << " |" << endl
             << endl
             << "\033[7;36m***********************************************************\033[0m" << endl
             << endl;

        cout << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;36m***********************************************************\033[0m" << endl;
    }
}

#define MAX_WAR 32.0f // max space in warehouse

void GUI::factory2map()
{
    float perc = (float)(MAX_WAR - messi->fac.remSpaceWar) / MAX_WAR;

    for (int i = 0; i < 9; i++)
    {
        if (perc >= (float)(i + 1.0f) / 9.0f)
        {
            if (perc >= 0.0f && perc < 0.34f)
                sprintf(map.warehouse[i], "\033[7;32m");
            else if (perc >= 0.34f && perc < 0.67f)
                sprintf(map.warehouse[i], "\033[7;33m");
            else if (perc >= 0.67f && perc <= 1.0f)
                sprintf(map.warehouse[i], "\033[7;31m");
            else
                sprintf(map.warehouse[i], "\033[7;32m");
        }
        else
            sprintf(map.warehouse[i], "\033[0m");
    }

    for (int i = 0; i < 41; i++)
        map.pos[i] = ' ';

    for (int i = 0; i < 128; i++)
    {
        if (messi->fac.pieces[i].pos >= 0)
            map.pos[messi->fac.pieces[i].pos] = '@';
    }
}

// | @ |   -------------------------------------------------
// | @ |    0   1   2   3   4    5   6   7    8   9   10  11  <
// | @ |   -------     ---          ---          ---     ---
// | @ |         | 12 |   | 13  14 |   | 15  16 |   | 17 | >
// | @ |         | 18 |   | 19  20 |   | 21  22 |   |    |
// | @ |         | 23 |   | 24  25 |   | 26  27 |   | 28 | >
// | @ |   -------     ---          ---          ---     ---
// | @ |    29  30  31  32  33   34  35  36  37  38  39  40  <
// | @ |   -------------------------------------------------

// cout << "| @ |   -------------------------------------------------   " << endl
//              << "| @ |    ¤   ¤   ¤   ¤   ¤    ¤   ¤   ¤    ¤   ¤   ¤   ¤    " << endl
//              << "| @ |   -------     ---          ---          ---     ---   " << endl
//              << "| @ |          | ¤ |   | ¤ || ¤ |   | ¤ || ¤ |   | ¤ |      " << endl
//              << "| @ |          | ¤ |   | ¤ || ¤ |   | ¤ || ¤ |   |   |      " << endl
//              << "| @ |          | ¤ |   | ¤ || ¤ |   | ¤ || ¤ |   | ¤ |      " << endl
//              << "| @ |   -------     ---          ---          ---     ---   " << endl
//              << "| @ |    ¤   ¤   ¤   ¤   ¤    ¤   ¤   ¤    ¤   ¤   ¤   ¤    " << endl
//              << "| @ |   -------------------------------------------------   " << endl
//              << endl;