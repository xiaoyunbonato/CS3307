#!/usr/bin/env bash
gcc sqlite3.c -c
g++ logger.cpp -c
g++ generator.cpp -c
g++ log_message.cpp -c
g++ generator.o logger.o sqlite3.o log_message.o -o generator 
./generator "Sky is blue" "Lemons are yellow" "Oranges are orange" "Flowers are pretty"