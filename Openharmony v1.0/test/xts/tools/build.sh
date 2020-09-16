#!/usr/bin/env sh
# Copyright (c) 2020 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

BASE_HOME=$(dirname $(dirname $(dirname $(cd `dirname $0`; pwd))))
PRODUCT=
PLATFORM=
PLATFORM_PARAM=
TARGET=
TARGET_PARAM=
WIFIIOT_OUTFILE=Hi3861_wifiiot_app_allinone.bin
DIST_DIR=$BASE_HOME/dist
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/communication_lite/lwip_hal:ActsLwipTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/communication_lite/softbus_hal:ActsSoftBusTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/communication_lite/wifiservice_hal:ActsWifiServiceTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/utils_lite/parameter_hal:ActsParameterTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/utils_lite/utilsfile_hal:ActsUtilsFileTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/iot_hardware_lite/wifiiot_hal:ActsWifiIotTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/kernel_lite/kernelcmsis_hal:ActsCMSISTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/kernel_lite/kernelkal_hal:ActsKalTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/hiviewdfx_lite/dfx_hal:ActsDfxFuncTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/utils_lite/kvstore_hal:ActsKvStoreTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/security_lite/datahuks_hal:ActsSecurityDataTest"
WIFIIOT_MODULES="${WIFIIOT_MODULES},//test/xts/acts/distributedschedule_lite/samgr_hal:ActsSamgrTest"

error_report() {
    echo "Error on line $1"
}
trap 'error_report $LINENO' ERR


usage()
{
  echo
  echo "USAGE"
  echo "       ./build.sh product=PRODUCT [platform=PLATFORM] [target=TARGET]"
  echo
  echo "                  product   : PRODUCT  product name, such as ipcamera or wifiiot"
  echo "                  platform  : PLATFORM  the platform of device, such as hi3518ev300 hi3516dv300"
  echo
  exit 1
}

check_python()
{
  python_cmd=
  ver=$(python -c 'import platform; major, minor, patch = platform.python_version_tuple(); print(major);')
  if [ "$ver" = "3" ];then
    python_cmd=python
  else
    ver=$(python3 -c 'import platform; major, minor, patch = platform.python_version_tuple(); print(major);')
    if [ "$ver" = "3" ];then
      python_cmd=python3
    fi
  fi
  if [ -z "$python_cmd" ];then
    echo "Enviroment variable 'python3' is required, and python verion must be greater than 3.7"
    exit 1
  fi
}

parse_cmdline()
{
  while [ -n "$1" ]
  do
    var="$1"
    OPTIONS=`echo ${var%%=*}`
    PARAM=`echo ${var#*=}`
    case "$OPTIONS" in
    product)   PRODUCT="$PARAM"
               ;;
    platform)  PLATFORM="$PARAM"
               ;;
    target)    TARGET="$PARAM"
               ;;
    *)   usage
         break;;
    esac
    shift
  done
  if [ "$PRODUCT" = "" ];then
    usage
  fi
  if [ "$PRODUCT" = "wifiiot" ];then
    PLATFORM="hi3861v100_liteos_riscv"
    PLATFORM_PARAM=""
    if [ "$TARGET" = "" ];then
      TARGET=$WIFIIOT_MODULES
    fi
  elif [ "$PLATFORM" = "" ];then
    echo "platform is required, for product $PRODUCT"
    usage
  else
    PLATFORM_PARAM=" --platform $PLATFORM"
  fi
  if [ "$TARGET" != "" ];then
    TARGET_PARAM=" --target $TARGET"
  fi
}

build()
{
  out_dir="${BASE_HOME}/out/${PRODUCT}"
  suite_root_dir="${out_dir}/suites"
  xts_root_dir="${suite_root_dir}/acts"
  suite_out_dir="${xts_root_dir}/testcases"
  suite_out_zip="${xts_root_dir}.zip"

  cd $BASE_HOME
  if [ "$PRODUCT" = "wifiiot" ]; then
    rm -rf $DIST_DIR
    mkdir -p $DIST_DIR
    IFS=',' read -r -a array <<< "$TARGET"
    echo "--------------------------------------------${array[@]}"
    set -e
    mkdir -p ${DIST_DIR}/json
	for index in "${!array[@]}"
	do
      python build.py $PRODUCT -b debug -t xts ${array[index]}
      suite_build_target=`echo "${array[index]}" | awk -F "[/:]" '{print $NF}'`
      module_list_file=$suite_out_dir/module_info.json
      suite_module_name=`python test/xts/tools/build/utils.py --method_name get_modulename_by_buildtaregt --arguments module_list_file=${module_list_file}#build_target=${suite_build_target}`
      subsystem_name=`python test/xts/tools/build/utils.py --method_name get_subsystem_name --arguments path=${array[index]}`
      python test/xts/tools/build/utils.py --method_name record_testmodule_info --arguments build_target_name=${suite_module_name}#module_name=${suite_module_name}#subsystem_name=${subsystem_name}#suite_out_dir=${DIST_DIR}/json
      mkdir -p ${suite_out_dir}/${subsystem_name}
      cp -f ${out_dir}/${WIFIIOT_OUTFILE} ${suite_out_dir}/${subsystem_name}/${suite_module_name}.bin
      rm -f ${suite_out_dir}/${subsystem_name}/*.a
      cp -rf ${xts_root_dir}  ${DIST_DIR}
	done
    cp -rf ${DIST_DIR}/acts ${suite_root_dir}
    cp -rf ${DIST_DIR}/module_info.json ${suite_out_dir}
    cd $suite_root_dir
    rm -f ${suite_out_zip}
    zip -rv ${suite_out_zip} acts
    rm -rf $DIST_DIR
  else
    python build.py ${PRODUCT}_${PARAM} -b debug -t xts
  fi
}

echo $BASE_HOME
check_python
parse_cmdline $@
build
