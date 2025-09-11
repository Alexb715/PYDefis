#/bin/bash
g++ --std=c++23 main.cpp -o main `pkg-config --cflags --libs opencv4`