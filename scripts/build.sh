#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

pushd $DIR/../build
mkdir build
pushd build

cmake ../
make -j 4

popd
popd