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