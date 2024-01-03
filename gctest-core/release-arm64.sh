#!/bin/bash

BUILD_DIR=build-arm64

rm -rf $BUILD_DIR

cmake   --no-warn-unused-cli                        \
        -DARM64:BOOL=TRUE                           \
        -S.                                         \
        -B $BUILD_DIR                               \
        -G "Unix Makefiles"                         \

cmake   --build $BUILD_DIR                          \
        --target all install package                \
        -j 14 --                                    \