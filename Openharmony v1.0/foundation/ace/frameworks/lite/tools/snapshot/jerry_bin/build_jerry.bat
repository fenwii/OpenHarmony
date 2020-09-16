@rem Copyright (c) 2020 Huawei Device Co., Ltd.
@rem Licensed under the Apache License, Version 2.0 (the "License");
@rem you may not use this file except in compliance with the License.
@rem You may obtain a copy of the License at
@rem
@rem     http://www.apache.org/licenses/LICENSE-2.0
@rem
@rem Unless required by applicable law or agreed to in writing, software
@rem distributed under the License is distributed on an "AS IS" BASIS,
@rem WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
@rem See the License for the specific language governing permissions and
@rem limitations under the License.

@echo off

python ../../../../../external/jerryscript/tools/build.py --mem-heap=16 --snapshot-exec=ON --snapshot-save=ON --profile=es5.1 --error-messages=ON --logging=ON --mem-stats=ON --jerry-cmdline-snapshot=ON
cp ..\..\..\..\..\external\jerryscript\build\bin\MinSizeRel\jerry.exe .\win\
cp ..\..\..\..\..\external\jerryscript\build\bin\MinSizeRel\jerry-snapshot.exe .\win\

