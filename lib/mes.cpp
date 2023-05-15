#include "mes.hpp"

MES::~MES()
{
    cout << "MES: adeus" << endl;
}

void MES::onMain()
{
    cout << "MES: tou vivo" << endl;

    while (1)
    {
        if (refresh(time_now))
        {
            addNumberOfOrders(1);
        }
    }
}

void MES::addNumberOfOrders(uint16_t number)
{
    orders += number;

    return;
}