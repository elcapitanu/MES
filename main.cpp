#include "main.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#include "lib/interface.hpp"
#include "lib/inputs.hpp"
#include "lib/mes.hpp"
#include "lib/tcp.hpp"
#include "lib/opc-ua.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        MES messi;
        KEY key;
        GUI gui(&messi, &key.input);
        Socket soc;
        OpcUa op;

        messi.start();
        key.start();
        gui.start();
        // soc.start();
        // op.start();

        while (key.input != 'x')
            ;

        // op.stop();
        // soc.stop();
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