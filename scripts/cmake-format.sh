#!/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Illegal number of arguments"
    echo "Usage: cmake-format.sh <project-dir>"
    exit 1
fi

cmake-format "$1/CMakeLists.txt" -o "$1/CMakeLists.txt"
