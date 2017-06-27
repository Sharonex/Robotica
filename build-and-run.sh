#!/bin/bash
pushd Debug
make clean
make
./ObstacleAvoid
popd
