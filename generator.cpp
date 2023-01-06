// Xiaoyun Bonato
// Generator class
// 4 October 2022

#include <iostream>
#include "logger.h"
#include <cstdlib>
#include <csignal>
#include <chrono>
#include <thread>
using namespace std;

void exit(sig_t value)
{
    exit(0);
}

int main(int argc, char **argv)
{
    string programName = argv[0];

    // Making sure it only outputs Generator
    int position = programName.rfind('/') + 1;
    string shortName = programName.substr(position);

    logger log = logger(shortName);

    vector<string> messages;

    // Pushing a singular message each loop
    for (int i = 1; i < argc; i++)
    {
        string oneMessage = argv[i];
        messages.push_back(oneMessage);
    }

    while (true)
    {
        int i = rand() % messages.size();
        string aMessage = messages[i];
        log.write(aMessage);
        this_thread::sleep_for(chrono::milliseconds((rand() % 10000) + 1000));
        signal(SIGINT, exit);
    }
}