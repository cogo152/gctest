#!/bin/bash

rm -rf build

rm -rf package

./release-arm32.sh

./release-arm64.sh

./release-local.sh