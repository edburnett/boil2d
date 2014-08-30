#!/usr/bin/bash

#g++ -c -std=c++11 game.cpp && g++ game.o -o game -lsfml-graphics -lGL -lsfml-window -lsfml-system -lBox2D && ./game
g++ -std=c++11 src/main.cpp src/functions.cpp src/states/*.cpp -o bin/main -I./include -I./include/states -I./include/entityx -lsfml-graphics -lGL -lsfml-window -lsfml-system -lBox2D && ./bin/main
