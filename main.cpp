#include <iostream>
#include "lib/time.hpp"
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
        OpcUa opcua;
        initTime();
        opcua.OpcUa_Connect();
        while (0)
        {
            if (refresh())
            {
                mes.addNumberOfOrders(1);
                gui.show(mes);
            }
        }

        return 0;
    }
    else if (argc == 2 && !strcmp(argv[1], "teste"))
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