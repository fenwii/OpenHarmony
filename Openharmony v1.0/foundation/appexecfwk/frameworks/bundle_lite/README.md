## Introduction

The implementation files of the corresponding `.h` files are provided at here and a tool `bm` can be utilized by developers to install, uninstall application or query some information of the specified application.

## Directions

```
.
├── BUILD.gn
├── include
│   ├── ability_info_utils.h                # to provide some function to set the elements of AbilityInfo.
│   ├── bundle_callback.h                   # to provide monitor mechanism of install states for other module in the system.
│   ├── bundle_callback_utils.h             # to define some data structs to obtain the specified information return from the BMS `Bunndle Manager Servcice`.
│   ├── bundle_info_utils.h                 # to provide some functions to set the elements of BundleInfo.
│   ├── bundle_self_callback.h              # to provide the callback mechanism of install function and uninstall function.
│   ├── convert_utils.h                     # to provide some functions to transform AbilityInfo and BundleInfo to string, and then to transport by ipc.
│   └── module_info_utils.h                 # to provide some function to set the elements of ModuleInfo.
├── README.md
└── src
    ├── ability_info.cpp
    ├── ability_info_utils.cpp
    ├── bundle_callback.cpp
    ├── bundle_callback_utils.cpp
    ├── bundle_info.cpp
    ├── bundle_info_utils.cpp
    ├── bundle_manager.cpp
    ├── bundle_self_callback.cpp
    ├── convert_utils.cpp
    ├── element_name.cpp
    ├── event_handler.cpp
    ├── module_info.cpp
    ├── module_info_utils.cpp
    └── token_generate.cpp

```
