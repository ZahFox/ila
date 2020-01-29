#!/bin/bash

mkdir build
pushd build
cmake ../
make -j 4
popd