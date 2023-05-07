#include "interface.hpp"

GUI::~GUI()
{
    system("clear");
}

void GUI::onMain()
{
    display.state = 0;

    while (1)
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
        cout << "*********************Menu**********************" << endl
             << endl
             << "a. MES1" << endl
             << "b. MES2" << endl
             << "c. MES3" << endl
             << endl
             << "x. Close" << endl
             << endl
             << "***********************************************" << endl
             << endl
             << "          " << ctime(&date) << endl
             << "***********************************************" << endl;
    }
    else if (display.state == 1)
    {
        cout << "*********************MES1**********************" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl
             << "Number of orders: " << messi->orders << endl
             << endl
             << "Server: " << messi->message << endl
             << endl
             << "************Ainda não faço nada :)*************" << endl;
    }
    else if (display.state == 2)
    {
        cout << "*********************MES2**********************" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl
             << "Number of orders: " << messi->orders << endl
             << endl
             << "Server: " << messi->message << endl
             << endl
             << "************Ainda não faço nada :)*************" << endl;
    }
    else if (display.state == 3)
    {
        cout << "*********************MES3**********************" << endl
             << endl
             << name << "      " << ctime(&date) << endl
             << endl
             << "Number of orders: " << messi->orders << endl
             << endl
             << "Server: " << messi->message << endl
             << endl
             << "************Ainda não faço nada :)*************" << endl;
    }
}