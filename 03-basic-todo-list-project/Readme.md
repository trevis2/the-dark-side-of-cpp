<h1/>CMake usage description https://cmake.org/ </h1>

CMake is a meta build system that uses scripts called CMakeLists to generate build files for a specific environment (for example, makefiles on Unix machines).Unlike many cross-platform systems, CMake is designed to be used in conjunction with the native build environment.

<h4/>Easiest CMakeLists.txt file description:</h4>

| Command   |      Effect      |
|----------|:-------------:|
| cmake_minimum_required(VERSION 3.13)|  Specifies the minimum required version of CMake. It is set to the version of CMake bundled in CLion (always one of the newest versions available). |
| project(cmake_testapp) |    Defines the project name according to what we provided during project creation.   |
| set(CMAKE_CXX_STANDARD 14) | Sets the CMAKE_CXX_STANDARD variable to the value of 14, as we selected when creating the project. |
| add_executable(cmake_testapp main.cpp) | Adds the cmake_testapp executable target which will be built from main.cpp. |


there are also a lot of commands with use of which you are able to prevent the build from failing and in place Cmake will notify you that for instance you do not have boost libraries filesystem and regex installed on your system. To do that you can use the following syntax:

find_package(Boost 1.45.0 COMPONENTS filesystem regex)


<h4/>Why use CMake ?</h4>

- Eases Make use
- Separate the compilation from the sources
- Multi-platfoms
- Very flexible
- Check if the libraries/programs are available on your system
- File generator (configure_file)
- Calling programs or scripts (doxygen)
- One of the new standards

<h4/>Some commonly used commands:</h4>

- message: prints given message
- cmake_minimum_required: sets minimum version of cmake to be used
- add_executable: adds executable target with given name
- add_library: adds a library target to be build from listed source files
- add_subdirectory: adds a subdirectory to build

There are also commands to enable developers write out conditional statements, loops, iterate on list, assignments:

- if, endif
- elif, endif
- while, endwhile
- foreach, endforeach
- list
- return
- set_property (assign value to variable.)

Indentation is not mandatory but suggested while writing CMake scripts. CMake doesn’t use ‘;’ to understand end of statement.

Environment variables are used to configure compiler flags, linker flags, test configurations for a regular build process. Compiler have to be guided to search for given directories for libraries.

Run the compilation:</h4>

- mkdir build
- cd build
- cmake ..
- make

Or the user may override the default generator with the -G option:

- mkdir build
- cd build
- cmake .. -G "MinGW Makefiles"
- make

<h4/>References:</h4>

https://medium.com/@onur.dundar1/cmake-tutorial-585dd180109b

https://cmake.org/cmake/help/latest/manual/cmake.1.html
