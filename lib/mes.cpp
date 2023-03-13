#include "mes.hpp"

using namespace MES;

Socket::Socket()
{
}

Socket::~Socket()
{
}

Database::Database()
{
}

Database::~Database()
{
}

void Algorithm::addNumberOfOrders(uint16_t number)
{
    orders += number;

    return;
}

Algorithm::Algorithm()
{
    orders = 0;
}

Algorithm::~Algorithm()
{
}