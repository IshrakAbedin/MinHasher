<!-- Written by Mohammad Ishrak Abedin-->
# Min-Hasher

### A simple min-hashing algorithm using C++ standard ranges library (for learning purpose)

An implementation of the basic min-hashing algorithm for Jaccard Similarity matching of sets.

## Requirements

 The project relies on **[PREMAKE](https://premake.github.io/)** meta build system and can be compiled in Windows or Linux using a preferred build system (Expected to use MSVC/Clang with Visual Studio for Windows and GCC with GNU Make for Linux). It assumes that you have Premake 5 or higher installed and it can be directly accessed through the system environment.

## Packages Required for Linux

+ GCC
+ Make
+ Premake 5.0


**C++ 20 or higher is required to compile since the project relies on `std::ranges`. The project is only written and tested for `x64` systems.**

## Building for Windows (MSVC and Visual Studio)

The Windows version is targeted towards MSVC/Clang using Microsoft Visual Studio. A Visual Studio version 2022 or Higher is recommended.

Run the following command to in the project root directory generate the project files for the respective version of Visual Studio.

```powershell
premake5 vs2022 # Pass respective Visual Studio version
```

At this point, a Visual Studio Solution (`MinHashing.sln`) will be generated. Open it with Visual Studio and build the project.


## Building for Linux (GCC and GNU Make)

Run the following command in the project root directory to generate the project files for GNU Make.

```bash
premake5 gmake2 # Generates Makefile
```

To build the application in *Release* mode, run:

```bash
make config=release # For building in Release mode
```

Or to build in *Debug* mode, run:

```bash
make config=debug # For building in Debug mode
```

## Using the Application

After building, the executable is located in `bin/Release/` or `bin/Debug/` based on the build configuration. 

## Using as a Library

It should be considered as a single header only library located as [`src/MinHasher.hpp`](./src/MinHasher.hpp). One should really not use this code except for learning purposes as it does not leverage any vector or parallel processing capabilities of the modern CPUs.