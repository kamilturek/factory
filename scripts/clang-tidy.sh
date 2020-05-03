#!/bin/bash

set -e

if [ $# -ne 1 ]; then
    echo "Illegal number of arguments"
    echo "Usage: clang-tidy.sh <project-dir>"
    exit 1
fi

files=$(find "$1"/src/ "$1"/include/ -name '*.cpp' -or -name '*.hpp')
# shellcheck disable=SC2086
clang-tidy -p "$1/build/" --extra-arg=-Wno-unknown-warning-option $files
