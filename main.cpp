#include <iostream>
#include "lib/driver.hpp"
#include "lib/interface.hpp"

using namespace Interface;

int main()
{
    GUI gui;
    while (1)
        gui.ui();

    return 0;
}