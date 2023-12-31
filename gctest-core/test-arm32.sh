#!/bin/bash

rm -rf build

cmake   --no-warn-unused-cli                        \
        -DARM32:BOOL=TRUE                           \
        -DOWN_TEST:BOOL=TRUE                        \
        -S.                                         \
        -B build                                    \
        -G "Unix Makefiles"                         \

cmake   --build build                               \
        --target all test                           \
        -j 14 --                                    \