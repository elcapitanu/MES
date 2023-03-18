#include "interface.hpp"

using namespace Interface;

void GUI::show(MES::Algorithm mes)
{
    system("clear");
    time(&date);
    cout << "*********************MES**********************" << endl
         << endl
         << name << "      " << ctime(&date) << endl
         << endl
         << "Number of orders: " << mes.orders << endl
         << endl
         << "Server: " << mes.message << endl
         << endl
         << "************Ainda não faço nada :)************" << endl;
}

GUI::GUI()
{
    name.append("Bernardo Gabriel");
}

GUI::~GUI()
{
}