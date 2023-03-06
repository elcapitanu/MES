#include <iostream>
#include "lib/driver.hpp"
#include "lib/interface.hpp"

using namespace Interface;

int main()
{
    GUI gui;
    while (1)
    {
        gui.show();
        std::cout << "ola\n";
        std::cout << sum(5.4f, 7.2f) << "\n";
    }
    return 0;
}