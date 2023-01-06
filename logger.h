// Xiaoyun Bonato
// Logger Header
// 4 October 2022

#include <string>
#include <sqlite3.h>
#include "log_message.h"
#include <vector>

class logger
{
private:
    std::string tableName;
    sqlite3 *db;

public:
    logger(std::string nameParam);

    ~logger();

    void write(std::string logMessage);

    std::vector<log_message> read_all();
};