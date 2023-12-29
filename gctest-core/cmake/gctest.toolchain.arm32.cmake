set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_CROSSCOMPILING TRUE)

set(CMAKE_C_COMPILER /usr/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/arm-linux-gnueabihf-g++)

list(APPEND CMAKE_FIND_ROOT_PATH /usr/arm-linux-gnueabihf)
list(APPEND CMAKE_INSTALL_RPATH /usr/arm-linux-gnueabihf/lib)

set(CMAKE_CROSSCOMPILING_EMULATOR /usr/bin/qemu-arm CACHE FILEPATH "Path to the emulator for the target system.")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)