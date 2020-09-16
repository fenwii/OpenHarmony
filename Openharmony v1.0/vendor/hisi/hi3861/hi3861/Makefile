# Copyright (c) 2020 HiSilicon (Shanghai) Technologies CO., LIMITED.
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
#
MAIN_TOPDIR = $(shell pwd)
export MAIN_TOPDIR

all:
	$(MAKE) -f non_factory.mk all

clean:
	$(MAKE) -f non_factory.mk clean

all_clean:
	$(MAKE) -f non_factory.mk all_clean

factory:
	$(MAKE) -f factory.mk all

clean_factory:
	$(MAKE) -f factory.mk clean

