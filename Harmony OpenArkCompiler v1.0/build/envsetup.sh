#!/bin/bash

curdir=`pwd`
unset MAPLE_ROOT
export MAPLE_ROOT=${curdir}
unset MAPLE_BUILD_CORE
export MAPLE_BUILD_CORE=${MAPLE_ROOT}/build/core
export PATH=$PATH:${MAPLE_ROOT}/src/bin
