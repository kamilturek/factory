#!/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Illegal number of arguments"
    echo "Usage: cppcheck.sh <project-dir>"
    exit 1
fi

cppcheck "$1/src/" --enable=all --suppressions-list="$1/scripts/suppressions.txt" --error-exitcode=1
