#include "main.hpp"

#include "lib/interface.hpp"
#include "lib/inputs.hpp"
#include "lib/mes.hpp"
#include "lib/tcp.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        KEY key;
        Socket soc;
        MES messi(&soc);
        GUI gui(&messi, &soc, &key.input);

        soc.start();
        messi.start();
        key.start();
        gui.start();

        while (key.input != 0x1b)
            ;

        gui.stop();
        key.stop();
        soc.stop();
        messi.stop();

        //system("clear");

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