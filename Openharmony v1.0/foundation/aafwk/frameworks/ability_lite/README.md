# AbilityKit - ability development kit

## Introduction

The cpp file is the implementation of AbilityKit class.

## Features

- provides methods for users to write their own applications.
- manage slices of the ability in an application
- create the application main thread and display the window

## Directions

```

.
└── ability_lite
    ├── BUILD.gn
    ├── include
    │   ├── ability_env_impl.h                # implementation of ability_env.h
    │   ├── ability_scheduler.h               # execute ability task from ability manager service
    │   ├── ability_service_manager.h         # manage the ability of service
    │   ├── ability_slice_manager.h           # manage the slice of the ability
    │   ├── ability_slice_route.h             # manage the entry of an ability
    │   ├── ability_slice_scheduler.h         # scheduler the slices of an ability
    │   ├── ability_slice_stack.h             # store all the slices in an ability and supply method to operate them
    │   ├── ability_thread.h                  # the main thread of the kit
    │   ├── ability_window.h                  # handle the window during a whole ability lifecycle
    │   └── app_info.h                        # a struct that records the information of an application
    ├── README.md
    └── src
        ├── ability.cpp
        ├── ability_context.cpp
        ├── ability_env.cpp
        ├── ability_env_impl.cpp
        ├── ability_loader.cpp
        ├── ability_manager.cpp
        ├── ability_scheduler.cpp
        ├── ability_service_manager.cpp
        ├── ability_slice.cpp
        ├── ability_slice_manager.cpp
        ├── ability_slice_route.cpp
        ├── ability_slice_scheduler.cpp
        ├── ability_slice_stack.cpp
        ├── ability_thread.cpp
        ├── ability_window.cpp
        └── main.cpp

```