#!/bin/bash
echo "Building project with cmake..."

cd "$(dirname "$0")"
SCRIPT_DIR="$(pwd)"
echo "Script directory: $SCRIPT_DIR"

cd build
cmake ../
cmake --build .

