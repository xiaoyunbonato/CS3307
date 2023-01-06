// Xiaoyun Bonato
// Logger class
// 4 October 2022

#include "logger.h"
#include <iostream>
#include <ctime>
#include <sstream>
using namespace std;

// Creating logger database

logger::logger(string nameParam)
{

    tableName = nameParam;
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("loggerDatabase", &db);

    // Create error message
    if (rc)
    {
        cerr << "Can't open database:" << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
    }

    // Creating table
    string sql = "CREATE TABLE IF NOT EXISTS ";
    sql += tableName;
    sql += " (timestamp varchar(255), message varchar(255));";
    rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_close(db);
        sqlite3_free(zErrMsg);
    }
}

logger::~logger()
{
}

// Creating write

void logger::write(string logMessage)
{
    // Finding timestamp

    time_t now;
    time(&now);
    char timestamp[sizeof "Wed Aug 10 22:32:24 2022"];
    strftime(timestamp, sizeof timestamp, "%a %b%e %T %Y", gmtime(&now));

    // Inserting timestamp and message into table
    stringstream sql;
    sql << "INSERT INTO " << tableName << " values (\"" << timestamp << "\", \"" << logMessage << "\")";

    string stringsql = sql.str();

    const char *c_version = stringsql.c_str();

    char *zErrMsg = nullptr;

    int rc = sqlite3_exec(db, c_version, nullptr, nullptr, &zErrMsg);

    if (rc != SQLITE_OK)
    {
        cerr << "SQL error: " << zErrMsg << endl;
        sqlite3_free(zErrMsg);
    }
}

vector<log_message> logger::read_all()
{
    stringstream ss;
    sqlite3_stmt *stmt;

    ss << "SELECT * from " << tableName;

    string sql = ss.str();

    // compile sql statement to binary
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("ERROR: while compiling sql: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
    }

    // execute sql statement, and while there are rows returned, print ID
    int ret_code = 0;
    vector<log_message> logMsgData;

    while ((ret_code = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        stringstream timestampStream;
        stringstream messageStream;
        timestampStream << sqlite3_column_text(stmt, 0);
        messageStream << sqlite3_column_text(stmt, 1);
        string timestamp = timestampStream.str();
        string message = messageStream.str();

        log_message logmsg = log_message(timestamp, message);

        logMsgData.push_back(logmsg); // adds an element to the end of the vector
    }

    if (ret_code != SQLITE_DONE)
    {
        //this error handling could be done better, but it works
        cerr << "ERROR: while performing sql: " << sqlite3_errmsg(db) << endl;
        cerr << "ret_code = " << ret_code << endl;
    }

    //release resources
    sqlite3_finalize(stmt);
    return logMsgData;
}