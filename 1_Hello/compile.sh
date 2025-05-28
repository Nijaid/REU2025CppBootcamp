# !/bin/bash

# Preprocess and compile
g++ -c Hello.cpp
# Link and compile executable
g++ -o Hello Hello.o

echo 'Hello is ready for execution'
