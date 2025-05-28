# 2_Orbit

This is a small C++ project that calculates the evolution of a binary system in Newtonian gravity. Poke around the code, and see the slides to understand its structure.

## Requirements
 To compile, we configure the build with CMake. [CMake](https://cmake.org/cmake/help/latest/) is a wonderful tool that manages the building of source code; you can find an introduction in the link. It generates Makefiles - instructions for compiling and installing and more - based on your hardware and other options that you may give the configuration. This allows for code to be portable across different systems. You should be able to install it using your favorite package manager. We will need at least version 4.0; most likely a newer version will be installed but that is not a problem.

 ## Generating the configuration
 We will not be going into the details of CMake, but you can take a look at the root [CMakeLists.txt](CMakeLists.txt) and its comments. To generate the configuration, first create a build directory and change your working directory to it,
 ```shell
 mkdir build
 cd build
 ```
 All of CMake's intermediate output will be placed in here, so if something goes wrong, it can just be deleted with `rm -rf *` and ran again.

 To generate, run
 ```shell
 cmake \
 -DCMAKE_BUILD_TYPE=Release \
 -DCMAKE_INSTALL_PREFIX=../ \
 -DCMAKE_BUILD_WITH_INSTALL_RPATH=True \
 ../
 ```
 The `-D` are options for the configuration; `CMAKE_BUILD_TYPE` determines some compilation options, such as the optimization, and `CMAKE_INSTALL_PREFIX` determines where the `install` targets will be placed. The install location is simply the root directory of the project, and is _not_ where things should be placed if they are to be used by other codes. (The common location is `/usr/local` although that may be different for M-chip Macs.) As the root directory is not a place expected for libraries to be installed (which is what our configuration will do), we specify with `CMAKE_BUILD_WITH_INSTALL_RPATH` that we want our install location to be used to link to the library (look inside the CMakeLists.txt for this option). The final argument is `../` which tells `cmake` where to look for the root CMakeLists.txt.

 ## Compiling and Installing
 If successful, `cmake` will have produced another copy of the source directory with the files it needs to compile the project. There should now be a `Makefile` in the current directory, and can be run with
 ```shell
 make
 ```
 If successful, all the necessary binaries have been compiled. We can now "install" the library that solves for orbits, `orbitsolver`, and an executable that uses it, `orbitExample`; `cmake`'s standard output will tell where they are. The installation is done with
 ```shell
 make install
 ```
 These are the usual steps for CMake projects. They are pretty straightforward for the user, and is why many developers have adopted CMake to distribute their code.
