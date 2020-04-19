#!/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Illegal number of arguments"
    echo "Usage: clang-tidy.sh <project-dir>"
    exit 1
fi

clang-tidy -p "$1/build/" --extra-arg=-Wno-unknown-warning-option "$1/src/"*
