#!/bin/bash

cd build

ctest -j14 -C Debug -T test --output-on-failure -R ^tutorial$