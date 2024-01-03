#!/bin/bash

BUILD_DIR=build-local

rm -rf $BUILD_DIR

cmake   --no-warn-unused-cli                        \
        -DOWN_TEST:BOOL=TRUE                        \
        -S.                                         \
        -B $BUILD_DIR                               \
        -G "Unix Makefiles"                         \

cmake   --build $BUILD_DIR                          \
        --target all test                           \
        -j 14 --                                    \