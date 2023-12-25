#!/bin/bash

rm -rf build

cmake   --no-warn-unused-cli                        \
        -DCMAKE_BUILD_TYPE:STRING=Debug             \
        -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE   \
        -DCMAKE_C_COMPILER:FILEPATH=/usr/bin/gcc    \
        -DCMAKE_CXX_COMPILER:FILEPATH=/usr/bin/g++  \
        -S.                                         \
        -B build                                    \
        -G "Unix Makefiles"                         \

cmake   --build build                               \
        --config Debug                              \
        --target all test install package           \
        -j 14 --                                    \

#dpkg-deb -R build/package/gctest-core_1.0.5_all.deb build/package-extract

#rpm2cpio build/package/gctest-core-1.0.5-1.noarch.rpm | cpio -imvd build/package-extract