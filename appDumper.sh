#!/usr/bin/env bash
gcc sqlite3.c -c
g++ logger.cpp -c
g++ dumper.cpp -c
g++ log_message.cpp -c
g++ dumper.o logger.o sqlite3.o log_message.o -o dumper
./dumper generator
