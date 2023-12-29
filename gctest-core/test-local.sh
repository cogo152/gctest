#!/bin/bash

rm -rf build

cmake   --no-warn-unused-cli                        \
        -DOWN_TEST:BOOL=TRUE                        \
        -S.                                         \
        -B build                                    \
        -G "Unix Makefiles"                         \

cmake   --build build                               \
        --config Debug                              \
        --target all test                           \
        -j 14 --                                    \