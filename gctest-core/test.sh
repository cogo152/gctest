#!/bin/bash

rm -rf build

cmake   --no-warn-unused-cli                        \
        -DCMAKE_BUILD_TYPE:STRING=Debug             \
        -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE   \
        -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc    \
        -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++  \
        -DOWN_TEST:BOOL=TRUE                        \
        -S.                                         \
        -B build                                    \
        -G "Unix Makefiles"                         \

cmake   --build build                               \
        --config Debug                              \
        --target all test                           \
        -j 14 --                                    \