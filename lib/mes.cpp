#include "mes.hpp"

MES::~MES()
{
}

void MES::onMain()
{
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