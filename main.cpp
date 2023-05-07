#include "main.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

#include "lib/interface.hpp"
#include "lib/inputs.hpp"
#include "lib/mes.hpp"

#include "threads/AbstractPipe.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        Pipeline::AbstractPipe<vector<int>> mintPipe("MES<->GUI");

        MES messi(&mintPipe);
        GUI gui(&mintPipe, &messi);
        KEY key(&mintPipe);

        gui.input = &key.input;

        messi.start();
        gui.start();
        key.start();

        while (1)
        {
            if (key.input == 'x')
            {
                messi.stop();
                gui.stop();
                key.stop();
                break;
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