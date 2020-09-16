#!/usr/bin/env sh
# Copyright (c) Huawei Technologies Co., Ltd. 2019. All rights reserved.

error()
{
  echo "$1"
  exit 1
}
PYTHON="python3"
TOOLS="tools"

flag=$(command -v $PYTHON | grep -c $PYTHON)
if [ "$flag" -eq 0 ]; then
    error "Python3.7 or higher version required!"
fi

$PYTHON -c 'import sys; exit(1) if sys.version_info.major < 3 or sys.version_info.minor < 7 else exit(0)' || \
error "Python3.7 or higher version required!"
cd $(dirname "$0") || error "Failure to change direcory!"
$PYTHON -c "import easy_install" || error "Please install setuptools first!"

if [ ! -d $TOOLS ]; then
  error "$TOOLS directory not exists"
fi

for f in "$TOOLS"/*.egg
do
  if [ ! -e "$f" ]; then
    error "Can not find xdevice package!"
  fi
  $PYTHON -m easy_install --user "$f" || echo "Error occurs to install $f!"
done

$PYTHON -m xdevice "$@"
