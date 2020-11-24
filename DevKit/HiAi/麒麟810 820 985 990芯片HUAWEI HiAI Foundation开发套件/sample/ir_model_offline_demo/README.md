# IR demo
The IR demo describes how to build a model offline using the SqueezeNet as an example. For details, see the makefile file.

## Table of Contents
* [Introduction](#Introduction)
* [Preparation && Getting Started](#Preparation && Getting Started)
* [Supported Environments](#Supported Environments)
* [Result](#Result)
* [License](#License)

## Introduction
For details about the app integration process, see Inference demo. Offline IR model building includes single-operator building, network building, and model building.

## Preparation && Getting Started
1. Call the buildSqueezenetGraph function to set the graph input and output to build a graph object.
2. Add the graph object to the model.
3. Call the BuildIRModel API to build the IR model offline.
4. Compile the source code like : make squeezenet.
5. Execute and generating model: ./squeezenet.

## Supported Environments
- Use Ubuntu 16.04 or later.

## Result
- Execute the compiled IR model executable file to generate an OM.

## License
- The sample of HUAWEI HiAI Foundation has obtained the [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0).