#include "inputs.hpp"

KEY::~KEY()
{
#if DEBUG_THR
    cout << "KEY: adeus" << endl;
#endif
}

void KEY::onMain()
{
#if DEBUG_THR
    cout << "KEY: tou vivo" << endl;
#endif

    while (!stopRequested())
    {
        cin >> input;
    }
}