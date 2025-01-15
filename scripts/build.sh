#!/bin/bash
# Build script for the project
mkdir -p build && cd build
cmake ..
make
