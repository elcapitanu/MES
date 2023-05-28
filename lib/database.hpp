#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../main.hpp"

#include <postgresql/libpq-fe.h>

class Database
{
private:
    const std::string kDbHostIP = "10.227.240.130";
    const std::string kDbName = "up201905660";
    const std::string kDbUsername = "up201905660";
    const std::string kDbPassword = "123456789";

    std::string dbconn_str = "dbname=" + kDbName + " host=" + kDbHostIP +
                             " user=" + kDbUsername + " password=" + kDbPassword +
                             " connect_timeout=2";

public:
    Database();
    ~Database();

    PGconn *dbconn = PQconnectdb(dbconn_str.c_str());

    void start();
    void stop();

    bool connectDatabase();
    int checkProgressWorking();
    void writeAlgorithm();
    void readAlgorithm();
    int CheckIsEmpty();
    void print_db(std::string db_name);
    int InsertRequest(int x);
    void saveMESmessage(char *msg, int day, int new_);
    char *getMESmessage(int *day);
    void CleanTable(std::string dbname);

    int UpdateTablePiece(int piece[9]);
    int UpdateTableDelivery(int delivery[2]);
    int UpdateTableMachine(int machine, int tool, int optime, int pieces[7]);

    int *GetTablePiece();
    int *GetTableDelivery();
    int *GetTableMachine(int Machine);
    
    int status = -1;
    bool connected = false;
};

#endif