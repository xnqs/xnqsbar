#!/bin/sh
mkdir -p build
g++ src/main.cxx src/utils.cxx src/kernel.cxx src/cpu.cxx src/ram.cxx src/swap.cxx src/date.cxx src/time.cxx -o build/main -O2
