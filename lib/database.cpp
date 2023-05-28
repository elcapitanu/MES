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
}

int Database::start()
{
    if (status < 0)
    {
        if (connectDatabase())
            status = 1;
        else
            status = -1;
    }

    return status;
}

void Database::stop()
{
    // write db status = -1
    if (status > 0)
    {
        PGresult *result;
        std::string order;
        CleanTable("mesorder");
        if (PQstatus(dbconn) == CONNECTION_OK)
        {
            order = "Update requests \n SET status = -1;";
            result = PQexec(dbconn, order.c_str());
            PQclear(result);
        }
    }
}

int Database::connectDatabase()
{
    PGresult *result;
    std::string order;
    if (PQstatus(dbconn) == CONNECTION_OK)
    {
        result = PQexec(dbconn, "SET search_path TO up201905660;");
        PQclear(result);
        result = PQexec(dbconn, "SHOW search_path;");
        PQclear(result);
        return 1;
    }
    else
        return 0;
}

int Database::checkProgressWorking()
{
    if (status > 0)
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
            return 1;
        }
        if (status && dbStatus)
        { // working with connection
            return 1;
        }
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
    if (status > 0)
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
    }
}

char *Database::getMESmessage(int *day)
{
    if (status > 0)
    {
        PGresult *result;
        std::string order;

        if (PQstatus(dbconn) == CONNECTION_OK)
        {
            order = "SELECT * FROM mesorder ;";
            result = PQexec(dbconn, order.c_str());
            int last = PQntuples(result);

            char *message = PQgetvalue(result, last - 1, 1);
            (*day) = atoi(PQgetvalue(result, last - 1, 0));

            PQclear(result);
            return message;
        }
    }
    return NULL;
}

void Database::CleanTable(std::string dbname)
{
    if (status > 0)
    {
        PGresult *result;
        std::string order;
        if (PQstatus(dbconn) == CONNECTION_OK)
        {
            order = "DELETE FROM " + dbname + ";";
            result = PQexec(dbconn, order.c_str());
            PQclear(result);
        }
    }
}