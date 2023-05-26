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
            // show();
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
            else if (*input == 'm')
                display.state = 21;
            else if (*input == 'd')
                display.state = 22;
        }
        else if (display.state == 21)
        {
            if (*input == 'q')
                display.state = 0;
            else if (*input == 's')
                display.state = 2;
            else if (*input == '1')
                display.state = 211;
            else if (*input == '2')
                display.state = 212;
            else if (*input == '3')
                display.state = 213;
            else if (*input == '4')
                display.state = 214;
        }
        else if (display.state == 211 || display.state == 212 || display.state == 213 || display.state == 214)
        {
            if (*input == 'q')
                display.state = 0;
            else if (*input == 's')
                display.state = 2;
            else if (*input == 'm')
                display.state = 21;
        }
        else if (display.state == 22)
        {
            if (*input == 'q')
                display.state = 0;
            else if (*input == 's')
                display.state = 2;
            else if (*input == '1')
                display.state = 221;
            else if (*input == '2')
                display.state = 222;
        }
        else if (display.state == 221 || display.state == 222)
        {
            if (*input == 'q')
                display.state = 0;
            else if (*input == 's')
                display.state = 2;
            else if (*input == 'd')
                display.state = 22;
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
             << "b. Show statistics" << endl
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
        cout << "\033[7;31m*********************MES***********************\033[0m" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl;
             
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
        cout << "\033[7;33m*********************STATISTICS**********************\033[0m" << endl
             << endl;

        cout << "m. Show Machine Statistics" << endl
             << endl
             << "d. Show Dock Statistics" << endl
             << endl
             << "\033[7;33m                                                     \033[0m" << endl
             << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;33m*****************************************************\033[0m" << endl;
    }
    else if (display.state == 21)
    {
        cout << "\033[7;33m*********************MACHINES**********************\033[0m" << endl
             << endl
             << "1. Show Machine 1 Statistics" << endl
             << endl
             << "2. Show Machine 2 Statistics" << endl
             << endl
             << "3. Show Machine 3 Statistics" << endl
             << endl
             << "4. Show Machine 4 Statistics" << endl
             << endl
             << "\033[7;33m                                                   \033[0m" << endl
             << endl
             << "s. Return to STATISTICS" << endl
             << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;33m***************************************************\033[0m" << endl;
    }
    else if (display.state == 211 || display.state == 212 || display.state == 213 || display.state == 214)
    {
        int machine = display.state - 210;

        cout << "\033[7;33m*****************************MACHINE " << machine << "*****************************\033[0m" << endl
             << endl
             << "                      Total operating time: " << messi->fac.machines[machine - 1].totalOperatingTime << endl
             << endl
             << "                          Worked Pieces" << endl
             << "            | P1: " << messi->fac.machines[machine - 1].operatedPieces[0] << " | P2: " << messi->fac.machines[machine - 1].operatedPieces[1] << " | P3: " << messi->fac.machines[machine - 1].operatedPieces[2] << " | P4: " << messi->fac.machines[machine - 1].operatedPieces[3] << " | P5: " << messi->fac.machines[machine - 1].operatedPieces[4] << " |" << endl
             << "                | P6: " << messi->fac.machines[machine - 1].operatedPieces[5] << " | P7: " << messi->fac.machines[machine - 1].operatedPieces[6] << " | P8: " << messi->fac.machines[machine - 1].operatedPieces[7] << " | P9: " << messi->fac.machines[machine - 1].operatedPieces[8] << " |" << endl
             << "                           | Total: " << messi->fac.machines[machine - 1].totalOperatedPieces << " |" << endl
             << endl;

        cout << "\033[7;33m*******************************************************************\033[0m" << endl
             << endl
             << "m. Return to Machine Statistics" << endl
             << endl
             << "s. Return to STATISTICS" << endl
             << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;33m*******************************************************************\033[0m" << endl;
    }
    else if (display.state == 22)
    {
        cout << "\033[7;33m*********************DOCKS**********************\033[0m" << endl
             << endl

             << "1. Show Dock 1 Statistics" << endl
             << endl
             << "2. Show Dock 2 Statistics" << endl
             << endl
             << "\033[7;33m                                                \033[0m" << endl
             << endl
             << "s. Return to STATISTICS" << endl
             << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;33m************************************************\033[0m" << endl;
    }
    else if (display.state == 221 || display.state == 222)
    {
        int dock = display.state - 220;

        cout << "\033[7;33m*******************************DOCK " << dock << "******************************\033[0m" << endl
             << endl;

        cout << "                         Unloaded Pieces" << endl
             << "            | P1: " << messi->fac.docks[dock - 1].unloadedPieces[0] << " | P2: " << messi->fac.docks[dock - 1].unloadedPieces[1] << " | P3: " << messi->fac.docks[dock - 1].unloadedPieces[2] << " | P4: " << messi->fac.docks[dock - 1].unloadedPieces[3] << " | P5: " << messi->fac.docks[dock - 1].unloadedPieces[4] << " |" << endl
             << "                | P6: " << messi->fac.docks[dock - 1].unloadedPieces[5] << " | P7: " << messi->fac.docks[dock - 1].unloadedPieces[6] << " | P8: " << messi->fac.docks[dock - 1].unloadedPieces[7] << " | P9: " << messi->fac.docks[dock - 1].unloadedPieces[8] << " |" << endl
             << "                           | Total: " << messi->fac.docks[dock - 1].totalUnloadedPieces << " |" << endl
             << endl;

        cout << "\033[7;33m*******************************************************************\033[0m" << endl
             << endl
             << "d. Return to Dock Statistics" << endl
             << endl
             << "s. Return to STATISTICS" << endl
             << endl
             << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;33m*******************************************************************\033[0m" << endl;
    }
    else if (display.state == 3)
    {
        cout << "\033[7;36m***************************Factory**********************************\033[0m" << endl
             << endl
             << "                           \033[7;37m Day: " << messi->day << " \033[0m" << endl
             << endl
             << "                        \033[7;37m   PROGRESS   \033[0m" << endl
             << "                        \033[7;37m  \033[0m          \033[7;37m  \033[0m" << endl
             << "                        \033[7;37m              \033[0m" << endl
             << endl
             << "\033[7;36m********************************************************************\033[0m" << endl
             << endl;

        factory2map();

        cout << " \033[7;37m      \033[0m" << endl
             << " \033[7;37mW " << map.warehouse[8] << "  \033[7;37m  \033[0m  \033[7;37m                                                          \033[0m   " << endl
             << " \033[7;37mA " << map.warehouse[7] << "  \033[7;37m  \033[0m  \033[7;34m " << map.pos[0] << "   " << map.pos[1] << "   " << map.pos[2] << "    " << map.pos[3] << "    " << map.pos[4] << "    " << map.pos[5] << "    " << map.pos[6] << "    " << map.pos[7] << "    " << map.pos[8] << "    " << map.pos[9] << "    " << map.pos[10] << "    \033[0m" << endl
             << " \033[7;37mR " << map.warehouse[6] << "  \033[7;37m  \033[0m  \033[7;37m        \033[7;34m   \033[7;37m       \033[7;34m   \033[7;37m  \033[7;34m   \033[7;37m       \033[7;34m   \033[7;37m  \033[7;34m   \033[7;37m       \033[7;34m   \033[7;37m       \033[0m" << endl
             << " \033[7;37mE " << map.warehouse[5] << "  \033[7;37m  \033[0m        \033[7;31mT" << messi->fac.machines[0].tool << "\033[7;34m " << map.pos[11] << " \033[7;37m  \033[0m   \033[7;37m  \033[7;34m " << map.pos[12] << " \033[7;37m  \033[7;34m   \033[7;37m  \033[0m   \033[7;37m  \033[7;34m   \033[7;37m  \033[7;34m " << map.pos[13] << " \033[7;37m  \033[0m   \033[7;37m  \033[7;34m " << map.pos[14] << " \033[7;31mD1\033[0m      " << endl
             << " \033[7;37mH " << map.warehouse[4] << "  \033[7;37m  \033[0m        \033[7;37m  \033[0m\033[7;34m " << map.pos[15] << " \033[7;37m  \033[0m   \033[7;31mT" << messi->fac.machines[2].tool << "\033[7;34m " << map.pos[16] << " \033[7;31mT" << messi->fac.machines[0].tool << "\033[7;34m " << map.pos[17] << " \033[7;37m  \033[0m   \033[7;37m  \033[7;34m   \033[7;37m  \033[7;34m   \033[7;37m  \033[0m   \033[7;37m  \033[7;34m   \033[7;37m  \033[0m      " << endl
             << " \033[7;37mO " << map.warehouse[3] << "  \033[7;37m  \033[0m        \033[7;31mT" << messi->fac.machines[1].tool << "\033[7;34m " << map.pos[18] << " \033[7;37m  \033[0m   \033[7;37m  \033[7;34m " << map.pos[19] << " \033[7;37m  \033[7;34m   \033[7;37m  \033[0m   \033[7;37m  \033[7;34m   \033[7;37m  \033[7;34m " << map.pos[20] << " \033[7;37m  \033[0m   \033[7;37m  \033[7;34m " << map.pos[21] << " \033[7;31mD2\033[0m      " << endl
             << " \033[7;37mU " << map.warehouse[6] << "  \033[7;37m  \033[0m  \033[7;37m        \033[7;34m   \033[7;37m       \033[7;34m   \033[7;37m  \033[7;34m   \033[7;37m       \033[7;34m   \033[7;37m  \033[7;34m   \033[7;37m       \033[7;34m   \033[7;37m       \033[0m" << endl
             << " \033[7;37mS " << map.warehouse[1] << "  \033[7;37m  \033[0m  \033[7;34m " << map.pos[22] << "   " << map.pos[23] << "   " << map.pos[24] << "    " << map.pos[25] << "    " << map.pos[26] << "    " << map.pos[27] << "    " << map.pos[28] << "    " << map.pos[29] << "    " << map.pos[30] << "     " << map.pos[31] << "   " << map.pos[32] <<  "    \033[0m" << endl
             << " \033[7;37mE " << map.warehouse[0] << "  \033[7;37m  \033[0m  \033[7;37m                                                          \033[0m   " << endl
             << " \033[7;37m      \033[0m" << endl
             << endl;

        cout << "\033[7;36m********************************************************************\033[0m" << endl
             << endl
             << "               Remaining space in the warehouse: " << messi->fac.remSpaceWar << endl
             << endl
             << "            | P1: " << messi->fac.p[0] << " | P2: " << messi->fac.p[1] << " | P3: " << messi->fac.p[2] << " | P4: " << messi->fac.p[3] << " | P5: " << messi->fac.p[4] << " |" << endl
             << "                | P6: " << messi->fac.p[5] << " | P7: " << messi->fac.p[6] << " | P8: " << messi->fac.p[7] << " | P9: " << messi->fac.p[8] << " |" << endl
             << endl
             << "              | M1: T" << messi->fac.machines[0].tool << " | M2: T" << messi->fac.machines[1].tool << " | M3: T" << messi->fac.machines[2].tool << " | M4: T" << messi->fac.machines[3].tool << " |" << endl
             << endl
             << "\033[7;36m********************************************************************\033[0m" << endl
             << endl;

        cout << "q. Return to MENU" << endl
             << endl
             << "esc. Close" << endl
             << endl
             << "\033[7;36m********************************************************************\033[0m" << endl;
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

    for (int i = 0; i < 33; i++)
    {
        if (messi->fac.sensors[i])
            map.pos[i] = '#';
        else
            map.pos[i] = ' ';
    }
}

// | @ |   -------------------------------------------------
// | @ |    0   1   2   3   4      5     6   7    8   9  10  <
// | @ |   -------     ---          ---          ---     ---
// | @ |         | 11 |   | 12     |   |     13 |   | 14 | >
// | @ |         | 15 |   | 16  17 |   |        |   |    |
// | @ |         | 18 |   | 19     |   |     20 |   | 21 | >
// | @ |   -------     ---          ---          ---     ---
// | @ |    22  23  24  25  26     27    28  29  30   31  32  <
// | @ |   -------------------------------------------------