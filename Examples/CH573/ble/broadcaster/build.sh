#!/bin/sh

EMB_GCC_PATH="$HOME/firmware/WCH/MRS_Toolchain_Linux_x64_V1.60/RISC-V Embedded GCC/bin"

export PATH="$EMB_GCC_PATH:$PATH"
make -C obj clean && make -C obj
