#!/bin/bash

RED='\033[0;31m'
NC='\033[0m' # No Color

rm -rf build
mkdir -p build
#(cd build-native && CC=clang CXX=clang++ cmake -DCMAKE_BUILD_TYPE=Debug ..)
(cd build && cmake ..)
retVal=$?
if [ $retVal -ne 0 ]; then
    echo "${RED}CMAKE FAILED${NC}"
    exit 1
fi
NPROC=$(sysctl -n hw.ncpu)
if [ -z $NPROC ]; then
    NPROC=$(nproc)
fi

#(cd build && make -j $NPROC)
(cd build && make VERBOSE=1 -j $NPROC)
retVal=$?
if [ $retVal -ne 0 ]; then
    echo "${RED}MAKE FAILED${NC}"
    exit 1
fi
(build/tests/cpptest 20)  