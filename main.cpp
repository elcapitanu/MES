#include <iostream>
#include "lib/driver.hpp"
#include "lib/interface.hpp"
#include "lib/mes.hpp"

#include <string.h>

using std::cin;
using std::cout;
using std::endl;

using namespace Interface;
using namespace MES;

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        GUI gui;
        Algorithm mes;

        while (1)
        {
            mes.addNumberOfOrders(1);
            gui.ui(mes);
        }

        return 0;
    }
    else if (argc == 2 && !strcmp(argv[1],"teste"))
    {
        cout << "MODO DE TESTE!" << endl;
        return 0;
    }
    else
    {
        cout << "NENHUM MODO!" << endl;
        return 0;
    }
}