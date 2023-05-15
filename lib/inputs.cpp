#include "inputs.hpp"

KEY::~KEY()
{
    cout << "KEY: adeus" << endl;
}

void KEY::onMain()
{
    cout << "KEY: tou vivo" << endl;

    while (1)
    {
        cin >> input;
    }
}