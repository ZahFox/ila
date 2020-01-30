#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

mkdir $DIR/../build
pushd $DIR/../build

cmake ../
make -j 4

popd