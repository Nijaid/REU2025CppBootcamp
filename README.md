# UIUC 2025 REU Physics C++ Bootcamp

Welcome! In this repo you will find two examples of C++ programs. As this session is only 2 hours long, the best way to introduce C++ for the REU is by exposure: take a look at the structure of the programs and familiarize yourself with how C++ looks and is used. Once you begin your research, you can anticipate how your C++ programs can be developed.

We start with a simple "Hello world" example in [1_Hello](1_Hello) (with a bit of a twist) to show some simple features of C++: the structure of a script and some basic compiling. [2_Orbit](2_Orbit) is an (almost) full-blown C++ project made with CMake; it may look complicated at first, but as you look through it and walk through how to use, it will become familiar. Remember, the goal here is to expose you to what C++ looks like, so you familarize yourself with its structure and design, so you may go out into research and know what to features to investigate.

Some basic material that can guide you is the free tutorial at [LearnC++](https://www.learncpp.com/).

## Requirements

If you have a command line, C++ compilers are usually included. A quick check is to run `gcc --version`, if you are using a Linux distribution, or `clang --version`, if you are on macOS. Usually Linux distros have the GNU Compiler Collection installed, or if on macOS, you will have Clang available if you have the Xcode command line tools installed. If you don't, see below; and if you do, make sure they are somewhat up-to-date. Xcode gets updated along with your OS, so as long as that is done, you are good; for Linux, you should `update` your package manager.

Besides having the compilers, you will need CMake to build the project in [2_Orbit](2_Orbit). This can be done with most package managers (recommended) or from [source](https://cmake.org/download/). We will need at least version 4.0.

### Installing GCC (Linux)
 
 Here we will refer to Ubuntu's `apt`, but it should be a similar syntax for other Linux distros. GCC can be easily installed after a quick update,
 ```shell
 sudo apt update
 sudo apt install build-essential
 ```
 `cmake` can be installed similarly.

 ### Installing Clang (macOS)
 
 To use the full features of macOS's command line, make sure Xcode's tools are installed. This can be checked with
 ```shell
 xcode-select -p
 ```
 You are in the green if the output is `/Applications/Xcode.app/Contents/Developer`. If instead you get `xcode-select: error: unable to get active developer directory`, you will need to install Xcode; in fact, the terminal may have already prompted you to do so. Either follow its instructions, or run
 ```shell
 xcode-select --install
 ```
 This will take a few minutes to install. Once done, use the checking command again and make sure the tools are installed!
 
 If the output of the check was anything else besides these two options, including if it had spaces in between directory names, or if the root folder was `Library`, you will need to do some more work. Go to https://mac.install.guide/commandlinetools/2 and find the output that matches yours and follow its instructions. You can follow the Homebrew instructions as well for installing the tools; Homebrew is a great package manager.