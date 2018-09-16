#!/bin/bash

## This is to run the first program main.cpp
rm main
cd Yinsh
g++ -o main main.cpp Board.cpp YinshBot.cpp
cp main ../
cd ..


