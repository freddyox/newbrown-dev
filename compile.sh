#!/bin/bash

echo "Compiling..."
echo " "
cd src/
g++ -c main.cpp Walls.cpp Ball.cpp BallManager.cpp Trace.cpp -I/Documents/SFML/SFML_SRC/include
echo "Linking..."
echo " "

mv *.o ../linkers
cd ../linkers

g++ main.o Walls.o Ball.o BallManager.o Trace.o -o brownian -L/Documents/SFML/SFML_SRC/lib -lsfml-graphics -lsfml-window -lsfml-system

mv brownian ../
cd ../

if [ -e compile.sh~ ] ;
then 
    rm compile.sh~ 
fi

echo "Executing..."
echo " "
./brownian

