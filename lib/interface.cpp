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
             << "x. Close" << endl
             << endl
             << "\033[7;32m***********************************************\033[0m" << endl
             << endl
             << "          \033[7;37m" << ctime(&date) << "\033[0m" << endl;

        if (!soc->isConnected())
        {
            cout << "            \033[5;31mNot connected to ERP\033[0m" << endl;
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
    }
    else if (display.state == 3)
    {
        cout << "\033[7;36m*******************Factory*********************\033[0m" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl
             << "          Space in the warehouse: " << messi->fac.war_space << endl
             << endl
             << "  | P1: " << messi->fac.p[0] << " | P2: " << messi->fac.p[1] << " | P3: " << messi->fac.p[2] << " | P4: " << messi->fac.p[3] << " | P5: " << messi->fac.p[4] << " |" << endl
             << "      | P6: " << messi->fac.p[5] << " | P7: " << messi->fac.p[6] << " | P8: " << messi->fac.p[7] << " | P9: " << messi->fac.p[8] << " |" << endl
             << endl
             << "    | M1: T" << messi->fac.m[0] << " | M2: T" << messi->fac.m[1] << " | M3: T" << messi->fac.m[2] << " | M4: T" << messi->fac.m[3] << " |" << endl
             << endl
             << "\033[7;36m***********************************************\033[0m" << endl
             << endl
             << "q. Return to MENU" << endl
             << endl
             << "x. Close" << endl
             << endl
             << "\033[7;36m***********************************************\033[0m" << endl;
    }
}