// Xiaoyun Bonato
// Dumper class
// 4 October 2022

#include <iostream>
#include "logger.h"
#include <cstdlib>
#include <csignal>
#include <chrono>
#include <thread>
using namespace std;

int main(int argc, char **argv)
{

    string app = argv[1];
    logger appDumper = logger(app);

    vector<log_message> logs = appDumper.read_all();

    for (int i = 0; i < logs.size(); i++)
    {

        log_message aLog = logs[i];
        string message = aLog.get_message();
        string timestamp = aLog.get_timestamp();
        cout << timestamp << ": " << message << endl;
    }
}