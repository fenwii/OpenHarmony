# IR demo
The IR demo describes how to build a model online using the SqueezeNet as an example. For details, see the createModel.cpp file.

## Table of Contents
* [Introduction](#Introduction)
* [Preparation && Getting Started](#Preparation && Getting Started)
* [Supported Environments](#Supported Environments)
* [Result](#Result)
* [License](#License)

## Introduction
For details about the app integration process, see Inference demo. Online IR model building includes single-operator building, network building, and model building.

## Preparation && Getting Started
1. Check whether the Android studio development is ready. To build this demo, please first import the demo in the Android Studio.
2. Call the buildSqueezenetGraph function to set the graph input and output to build a graph object.
3. Add the graph object to the model.
4. Call the BuildIRModel API to build the IR model online.
5. Run the sample on your Android device or emulator.

## Supported Environments
- Use Ubuntu 16.04, Windows 10, or macOS to install Android Studio 3.5.3 or later
- Build native code with NDK R14b or later

## Result
<img src="app/src/result.png" height="534" width="300"/>

## License
- The sample of HUAWEI HiAI Foundation has obtained the [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0).