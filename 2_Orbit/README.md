# 2_Orbit

This is a small C++ project that calculates the evolution of a binary system in Newtonian gravity. Poke around the code, and see the slides to understand its structure.

## Requirements
- CMake:
 To compile, we configure the build with CMake. [CMake](https://cmake.org/cmake/help/latest/) is a wonderful tool that manages the building of source code; you can find an introduction in the link. It generates Makefiles - instructions for compiling and installing and more - based on your hardware and other options that you may give the configuration. This allows for code to be portable across different systems. You should be able to install it using your favorite package manager. We will need at least version 4.0; most likely a newer version will be installed but that is not a problem.

- GSL:
The numerical integration will be done with functions from the [GNU Scientific Library](https://www.gnu.org/software/gsl/doc/html/ode-initval.html#). This should also be widely available on package managers. On APT, you may have to look for the `libgsl-dev` package.

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

 ## Code development
 The beauty of these Makefiles is that they keep track of how files depend on each other. When changes are made to a file, `make` know what files depend on it so that they are also re-compiled, while leaving other files alone. New files have to be added to the CMakeLists, which then have to be re-configured, in order for this to work.


## Execution

The project should have installed in the `bin` directory, where you should find the executable `orbitExample`. This is set up to integrate the evolution of the orbital phase $\phi(t)$ (see the [section below](#the-two-body-problem)) for the Sun-Earth system; take a look at its source file in the `app` directory. Its usage is, if you're in `bin`
```shell
./orbitExample NAME
```
where `NAME` will be used to name the output data file.
This output is a simple text file with a header and two columns: time $t$ and $\phi(t)$. You can see what the first ten lines of it look like by running `head NAME`.

### Visualization

If you have `Python`, `numpy`, and `matplotlib`, then you can run a Python script set up in the `python` directory that can make a quick plot. With it as the working directory, one can run
```shell
python plot_orbit.py ../bin/NAME
```
and a figure will open up.

## Going Beyond

It may have been a lot of information, but it can be learned and absorbed over time as you revisit and study it on your own. Here are some things to make you think about improvements that could be done:
- The output so far is only for $\phi(t)$. How would you obtain the evolution of the separation vector?
- The integration method implemented is only one of several. Are there better alternatives? The Newtonian problem is conservative; there are integration methods designed for such problems, but are not implemented in GSL. Maybe you can write your own!


# The Two-Body Problem

A background on the physics problem we're tryng to solve here can be found in [the PDF](two-body-problem.pdf).