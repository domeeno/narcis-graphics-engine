#!/bin/bash

cmake -B ./build
cd ./build
make
cd ..
./build/WallachiaStore

