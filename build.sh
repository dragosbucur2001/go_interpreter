#!/bin/bash

mkdir -p .build/debug
mkdir -p .build/release

CORES=$(nproc)
cmake -G Ninja -S . -B .build/debug
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S . -B .build/release

if [[ $1 == "release" ]]
then
    cd .build/release
    echo "Building Release"
else
    cd .build/debug
    echo "Building Debug"
fi

ninja
cp compile_commands.json ../../
cd ../../

