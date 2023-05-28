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
    int status;

public:
    PGconn *dbconn = PQconnectdb(dbconn_str.c_str());

    int connectDatabase();
    int checkProgressWorking();
    void writeAlgorithm();
    void readAlgorithm();
    int CheckIsEmpty();
    void print_db(std::string db_name);
    int InsertRequest(int x);
    void saveMESmessage(char *msg, int day);
    char *getMESmessage(int *day);

    void start();
    void stop();

    Database();
    ~Database();
};

#endif