# Overview<a name="EN-US_TOPIC_0000001051452141"></a>

This document describes the basic concepts of a bundle and how to define it in compliance with specifications.

## Definition<a name="section177563344911"></a>

OpenHarmony software is developed on a per-bundle basis. In terms of the operating system, all software running on OpenHarmony are bundles. Generally, bundles are classified into the following types based on their application scopes:

-   Board-level bundles: device hardware-specific bundles, such as  **board**,  **arch**, and  **mcu**
-   System-level bundles: a set of bundles with independent features, such as the kernel, file system, and framework
-   Application-level bundles: applications that provide services to users, such as  **wifi\_iot**  and  **ip\_camera**

Bundles are designed for the reuse purpose. Any reusable modules can be defined as bundles. They are classified into the following types based on their forms:

-   Source code
-   Binary system
-   Code snippet
-   Distribution

## Bundle Division Principles<a name="section2487162541016"></a>

In principle, bundles should be grouped at a fine-grained granularity as much as possible to achieve maximum reuse. The following factors are taken into account regarding bundle division:

-   Independence: Bundles provide relatively independent features and can be independently compiled. Each of them is capable of providing its own APIs and services for external systems.
-   Coupling: If a bundle must depend on another bundle to provide services, they can be coupled to one bundle.
-   Correlation: If a group of bundles jointly implement a feature, and if other bundles never depend on them, the group of bundles can be combined into one bundle.

## Bundle Dependency<a name="section185955409107"></a>

A bundle dependency can be mandatory or optional.

-   Mandatory dependency: If bundle A must depend on bundle B to implement a feature, that is, the APIs or services specific to bundle B must be invoked, then bundle B is defined as the mandatory dependency of bundle A.
-   Optional dependency: If either bundle C or bundle D is required for bundle A to implement a feature, and if bundle C and bundle D are interchangeable, then bundle C and bundle D are defined as optional dependencies of bundle A.

