# HDF Overview<a name="EN-US_TOPIC_0000001051611604"></a>

## Introduction<a name="section0649162112376"></a>

The OpenHarmony Driver Foundation \(HDF\) provides the following driver framework capabilities: driver loading, driver service management, and driver message mechanism. This unified driver architecture platform is designed to provide a more precise and efficient development environment, where you can perform one-time development and multi-system deployment.

## Driver Loading<a name="section68701942154319"></a>

Both on-demand loading and sequential loading are supported.

-   On-demand loading

    Drivers can be loaded by default during the operating system \(OS\) startup or be loaded dynamically after the OS startup.

-   Sequential loading

    Drivers can be loaded based on their priorities during the OS startup.


## Driver Service Management<a name="section12453133414412"></a>

The HDF centrally manages driver services. You can directly obtain a specified driver service by using the API provided by the HDF.

## Driver Message Mechanism<a name="section129410710451"></a>

The HDF provides a unified driver message mechanism, which allows message interactions between user-level applications and kernel-level drivers.

