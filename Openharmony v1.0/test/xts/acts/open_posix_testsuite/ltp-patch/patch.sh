#!/bin/bash
echo "Patching..."

cd ../../../../../../

project_path=$(pwd)

echo $project_path

patch -p0 third_party/ltp/testcases/open_posix_testsuite/scripts/generate-makefiles.sh < ./test/xts/acts/open_posix_testsuite/ltp-patch/generate-makefiles.sh.patch

echo "\n\n\n"

patch -p0 third_party/ltp/testcases/open_posix_testsuite/CFLAGS < ./test/xts/acts/open_posix_testsuite/ltp-patch/CFLAGS.patch

echo "\n\n\n"
