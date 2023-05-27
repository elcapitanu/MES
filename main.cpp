#include "main.hpp"

#include "lib/interface.hpp"
#include "lib/inputs.hpp"
#include "lib/mes.hpp"
#include "lib/tcp.hpp"
#include "lib/opc-ua.hpp"
#include "lib/database.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        KEY key;
        Socket soc;
        OpcUa op;
        Database db;
        MES messi(&soc, &op, &db);
        GUI gui(&messi, &soc, &key.input);

        op.start();
        messi.start();
        key.start();
        gui.start();
        soc.start();

        while (key.input != 0x1b)
            ;

        soc.stop();
        gui.stop();
        key.stop();
        messi.stop();

        system("clear");

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

    return -1;
}