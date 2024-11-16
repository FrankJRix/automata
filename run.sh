#!/bin/bash
echo "Running project..."
echo

cd "$(dirname "$0")"

./build/apps/automata_app "$@"

echo
