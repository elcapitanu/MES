#include <iostream>
#include "lib/time.hpp"
#include "lib/interface.hpp"
#include "lib/mes.hpp"

#include <string.h>

#include <string>

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

        initTime();

        mes.connectToERP();

        while (1)
        {
            
            if (mes.receiveValuesFromERP() == -1)
                break;

            if (refresh())
            {
                if (mes.sendValuesToERP() == -1)
                    break;

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