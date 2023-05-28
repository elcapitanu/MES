#include "database.hpp"

Database::Database()
{
#if DEBUG_THR
    cout << "Database: ola" << endl;
#endif
}

Database::~Database()
{
#if DEBUG_THR
    cout << "Database: adeus" << endl;
#endif
    stop();
}

void Database::start()
{
    connected = connectDatabase();
}

void Database::stop()
{
    // write db status = -1

    PGresult *result;
    std::string order;
    CleanTable("mesorder");
    UpdateDefault();
    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        order = "Update requests \n SET status = -1;";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);
    }

    connected = false;
}

bool Database::connectDatabase()
{
    PGresult *result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        result = PQexec(dbconn, "SET search_path TO up201905660;");
        PQclear(result);
        result = PQexec(dbconn, "SHOW search_path;");
        PQclear(result);
        return true;
    }
    else
        return false;
}

int Database::checkProgressWorking()
{
    PGresult *result;
    std::string order;
    int dbStatus; // get this value from database

    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        order = "SELECT status FROM requests;";
        result = PQexec(dbconn, order.c_str());
        dbStatus = atoi(PQgetvalue(result, 0, 0));
        PQclear(result);
    }
    else
        connected = false;

    if (status == -1 && dbStatus == 1)
    { // previously working
        return -1;
    }
    if (status == -1 && dbStatus == -1)
    { // start working
        status = 1;
        // write status on database
        PGresult *result;
        std::string order;
        if (PQstatus(dbconn) == CONNECTION_OK)
        {
            order = "Update requests \n SET status = 1;";
            result = PQexec(dbconn, order.c_str());
            PQclear(result);
        }
        else
            connected = false;

        return 1;
    }
    if (status && dbStatus)
    { // working with connection
        return 1;
    }

    return -1;
}

void Database::writeAlgorithm()
{
}

void Database::readAlgorithm()
{
}

void Database::saveMESmessage(char *msg, int day, int new_)
{

    PGresult *result;
    std::string order;
    std::string str(msg);
    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        if (new_)
            order = "INSERT INTO mesorder (day, message) VALUES ('" + std::to_string(day) + "','" + str + "');";
        else
            order = "UPDATE  mesorder SET message = '" + str + "' WHERE day = '" + std::to_string(day) + "' ;";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);
    }
    else
        connected = false;
}

char *Database::getMESmessage(int *day)
{

    PGresult *result;
    std::string order;

    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        order = "SELECT * FROM mesorder ;";
        result = PQexec(dbconn, order.c_str());
        int last = PQntuples(result);
        if(last == 0)
            return NULL;

        char *message = PQgetvalue(result, last - 1, 1);
        (*day) = atoi(PQgetvalue(result, last - 1, 0));

        PQclear(result);
        return message;
    }
    else
        connected = false;

    return NULL;
}

void Database::CleanTable(std::string dbname)
{

    PGresult *result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        order = "DELETE FROM " + dbname + ";";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);
    }
    else
        connected = false;
}


int Database::UpdateTablePiece(int piece[9]){
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK) {
        for(int i=1; i<10; i++){
            order = "UPDATE table_piece \n SET number_total_piece ='" + std::to_string(piece[i-1]) + 
                    "'WHERE piece = '" + std::to_string(i) + "';";
            result = PQexec(dbconn, order.c_str());
            PQclear(result);
        }
        return 1;
    }
    return -1;
}

int Database::UpdateTableDelivery(int delivery[2]){
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK) {

        std::string order = "UPDATE table_delivery SET delivered_1 = " + std::to_string(delivery[0]) +", delivered_2 = " + std::to_string(delivery[1]) + ";";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);

        return 1;
    }
    return -1;
}

int Database::UpdateTableMachine(int machine, int tool, int optime, int pieces[7]){
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK) {

        order = "UPDATE table_machine SET tool = " + std::to_string(tool) +
                            ", total_op_time = " + std::to_string(optime) +
                            ", piece_3 = " + std::to_string(pieces[0]) +
                            ", piece_4 = " + std::to_string(pieces[1]) +
                            ", piece_5 = " + std::to_string(pieces[2]) +
                            ", piece_6 = " + std::to_string(pieces[3]) +
                            ", piece_7 = " + std::to_string(pieces[4]) +
                            ", piece_8 = " + std::to_string(pieces[5]) +
                            ", piece_9 = " + std::to_string(pieces[6]) +
                            " WHERE machine = " + std::to_string(machine) + " ;";

        result = PQexec(dbconn, order.c_str());
        PQclear(result);

        return 1;
    }
    return -1;
}

void Database::GetTablePiece(int p[9]) {
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK) {
        order = "SELECT number_total_piece FROM table_piece;";
        result = PQexec(dbconn, order.c_str());

        for (int i = 0; i < 9; i++) {
            p[i] = atoi(PQgetvalue(result, i, 0));
        }
        PQclear(result);

        return;
    }
    return ;
}

int Database::GetTableDelivery(int dock) {
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK) {
        order = "SELECT * FROM table_delivery;";
        result = PQexec(dbconn, order.c_str());

        int pieces = atoi(PQgetvalue(result, 0, dock-1));

        PQclear(result);

        return pieces;
    }
    return 0;
}

void Database::GetTableMachine(int machine, int *tool, int *tottime, int piece[7]) {
    PGresult* result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK) {
        order = "SELECT tool, total_op_time, piece_3, piece_4, piece_5, piece_6, piece_7, piece_8, piece_9 FROM table_machine WHERE machine = " + std::to_string(machine) + ";";
        result = PQexec(dbconn, order.c_str());

        int* pieces = new int[9];
        for (int i = 0; i < 9; i++) {
            pieces[i] = atoi(PQgetvalue(result, 0, i));
        }
        *tool = pieces[0];
        *tottime = pieces[1];
        for (int i = 0; i < 7; i++) {
            piece[i] = pieces[i+2];
        }

        PQclear(result);
        return;
    
        PQclear(result);
    }
    return;
}

int Database::UpdateDefault(){
    PGresult* result;
    std::string order;

    if (PQstatus(dbconn) == CONNECTION_OK) {

        std::string order;
        order = "UPDATE table_delivery SET delivered_1 = " + std::to_string(0) +", delivered_2 = " + std::to_string(0) + ";";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);

        for(int i=1; i<10; i++){
            order = "UPDATE table_piece \n SET number_total_piece ='" + std::to_string(0) + 
                        "'WHERE piece = '" + std::to_string(i) + "';";
            result = PQexec(dbconn, order.c_str());
            PQclear(result);
        }

        for(int i=1; i<5; i++){
            order = "UPDATE table_machine SET tool = " + std::to_string(1) +
                    ", total_op_time = " + std::to_string(0) +
                    ", piece_3 = " + std::to_string(0) +
                    ", piece_4 = " + std::to_string(0) +
                    ", piece_5 = " + std::to_string(0) +
                    ", piece_6 = " + std::to_string(0) +
                    ", piece_7 = " + std::to_string(0) +
                    ", piece_8 = " + std::to_string(0) +
                    ", piece_9 = " + std::to_string(0) +
                    " WHERE machine = " + std::to_string(i) + " ;";

            result = PQexec(dbconn, order.c_str());
            PQclear(result);
            }

        order = "UPDATE table_machine SET tool = " + std::to_string(2) + " WHERE machine = 3;";
        result = PQexec(dbconn, order.c_str());
        PQclear(result);

        return 1;
    }
    return -1;
}