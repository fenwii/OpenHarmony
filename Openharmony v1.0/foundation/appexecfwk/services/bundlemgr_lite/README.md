# BMS - Bundle manager service of OpenHarmony

## Introduction

`Bundle manager service` (BMS) is aiming at installing/uninstalling application and managing bundleInfo.

## Features

- install application, include read files, parse files, create files, write to files and remove files. 
- uninstall application
- manage bundleInfo
- a `bm` tool who has capacity to install, uninstall applications and to dump some information of the specified applications.

## Directions

```
.
├── BUILD.gn
├── include
│   ├── bundle_common.h                      # common setting info
│   ├── bundle_extractor.h                   # bundle extractor
│   ├── bundle_installer.h                   # implementation of installing and uninstalling bundle
│   ├── bundle_manager_service.h             # bundle service task initialize and implementation of message process
│   ├── bundle_map.h                         # manage bundleInfo
│   ├── bundle_message_id.h                  # bundle message id setting
│   ├── bundle_ms_feature.h                  # BMS feature in Service Manager
│   ├── bundle_ms_host.h                     # register BMS in the Service Manager
│   ├── bundle_parser.h                      # parser bundle
│   ├── bundle_util.h                        # bundle util method
│   ├── extractor_util.h                     # extractor util method
│   ├── hap_sign_verify.h                    # verify signature of the hap package
│   └── zip_file.h                           # zip or unzip the hap package
├── README.md
├── src
│   ├── bundle_extractor.cpp
│   ├── bundle_installer.cpp
│   ├── bundle_manager_service.cpp
│   ├── bundle_map.cpp
│   ├── bundle_ms_feature.cpp
│   ├── bundle_ms_host.cpp
│   ├── bundle_parser.cpp
│   ├── bundle_util.cpp
│   ├── extractor_util.cpp
│   ├── hap_sign_verify.cpp
│   └── zip_file.cpp
└── tools
    ├── BUILD.gn
    ├── include
    │   └── command_parser.h
    └── src
        ├── command_parser.cpp
        └── main.cpp

```