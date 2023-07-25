#!/bin/bash

mkdir -p build/debug
mkdir -p build/release

CORES=$(nproc)
cmake -G Ninja -S . -B build/debug
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S . -B build/release
