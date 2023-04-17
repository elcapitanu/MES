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

        mes.init_t = initTime(mes.time_now);

        cout << "Waiting for ERP...\n";
        while (mes.connectToERP() == -1)
        {
            cout << "Failed to connect to ERP :(\n";
            return 0;
        }
        cout << "Connected to ERP\n";

        cout << "Waiting for PLC...\n";
        while (mes.connectToPLC() == -1)
        {
            cout << "Failed to connect to PLC :(\n";
            return 0;
        }
        cout << "Connected to PLC\n";

        mes.sendValuesToPLC();

        while (1)
        {
            mes.receiveValuesFromERP();

            if (refresh(mes.time_now))
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