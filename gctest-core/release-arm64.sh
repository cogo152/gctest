#!/bin/bash

rm -rf build

cmake   --no-warn-unused-cli                        \
        -DARM64:BOOL=TRUE                           \
        -S.                                         \
        -B build                                    \
        -G "Unix Makefiles"                         \

cmake   --build build                               \
        --config Debug                              \
        --target all install package                \
        -j 14 --                                    \