#include "mes.hpp"

using namespace MES;

Socket::Socket()
{
}

Socket::~Socket()
{
}

OpcUa::OpcUa()
{
}

OpcUa::~OpcUa()
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