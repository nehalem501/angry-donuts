#!/bin/bash

# We can lauch the script from anywhere with this
ROOTDIR=$(cd "${0%/*}" && echo $PWD)
cd "$ROOTDIR"

mkdir -p data
nodejs index.js
