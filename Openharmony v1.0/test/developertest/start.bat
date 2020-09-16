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

set BASE_HOME_PATH=%CD%

@echo start time is:
TIME /T

cd %BASE_HOME_PATH%\src

if exist %BASE_HOME_PATH%\python\python.exe (
    %BASE_HOME_PATH%\python\python.exe -m xdevice %1
) else (
    python -m main %1
)

%BASE_HOME_PATH%\python\python.exe -m xdevice %1
cd %BASE_HOME_PATH%

@echo finish time is:
TIME /T
@echo on
