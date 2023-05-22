#include "main.hpp"

#include "lib/interface.hpp"
#include "lib/inputs.hpp"
#include "lib/mes.hpp"
#include "lib/tcp.hpp"
#include "lib/opc-ua.hpp"

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        KEY key;
        Socket soc;
        OpcUa op;
        MES messi(&soc, &op);
        GUI gui(&messi, &soc, &key.input);
        Database db;

        if(!db.connectDatabase()){
            cout << "Not connected to Database\n";
            return 0;
        }
        if(db.checkProgressWorking() == -1){
            //read from db following commands to procede floor work


        }
        
        messi.start();
        key.start();
        gui.start();
        soc.start();
        op.start();

        while (key.input != 0x1b)
            ;

        op.stop();
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