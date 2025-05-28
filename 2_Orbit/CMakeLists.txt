#########################
## CMAKE for tutorial
## CMake is a useful tool to configure a C/C++ project (and other languages).
## It determines how to compile your project given your option and hardware,
## and generates the instructions needed.
## Place this file in the top level directory of your project,
## but run it from within the build directory.
## Once you are in build, execute the following command,
## > cmake ../
## This generates output that is then placed in build.
## The key output is the Makefile in this same directory.
## From here, you can execute it as usual,
## > make
## and the code will be compiled.
## If there are programs to be installed, run
## > make install
## All the build steps can be run together with
## > cmake --build ../
## but running them separately is better for debugging.
## Feel free to copy this for your own projects!
##########################


# Set the mininum CMake version
# If your CMake is not up-to-date, it will fail. Keep your modules up to date!
cmake_minimum_required(VERSION 4.0)

# Define your project
# Give some VERSION number and define the LANGUAGE your code supports
# By default C/C++ are supported but let's just include them
project(OrbitSolverExample VERSION 0.1
    LANGUAGES CXX)
# Three varriables are now set:
# - PROJECT_SOURCE_DIR, <PROJECT-NAME>_SOURCE_DIR
#   Absolute path to the source directory for the project.
# - PROJECT_BINARY_DIR, <PROJECT-NAME>_BINARY_DIR
#   Absolute path to the binary directory for the project.
# - PROJECT_IS_TOP_LEVEL, <PROJECT-NAME>_IS_TOP_LEVEL
#   Boolean value indicating whether the project is top-level.

# Let's nicely support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# Set where the INCLUDE directories are
# include_directories("${PROJECT_BINARY_DIR}")

# Set creating shared libraries as default
# Adding -DBUILD_SHARED_LIBS=0 at the configuration command turns it off
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# Specify the rpath so our library can be linked to
if(CMAKE_BUILD_WITH_INSTALL_RPATH)
  set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
endif()

# Use an interface to set compiler options.
# Note the use of ${PROJECT_NAME}, which substitutes in the project name
add_library(${PROJECT_NAME}_compiler_flags INTERFACE)

# Find external libraries.
# The REQUIRED option will cause the configuration to fail if the lbrary is not found
find_package(GSL REQUIRED)
# Attach the library directories to the interface
target_include_directories(${PROJECT_NAME}_compiler_flags INTERFACE "${GSL_INCLUDE_DIR}")

# Let's ensure -std=c++xx is used instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Set CXX standard
# This ensures the user has the necessary standard libraries
target_compile_features(${PROJECT_NAME}_compiler_flags INTERFACE cxx_std_17)

# Define the compiler warning flags
# The generator expression <COMPILE_LANG_AND_ID:...> returns true ("1") if 
# the compiler language is one of those in the ... list, otherwise returns 0.
# set() stores the value in gcc_like_cxx
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
# If gcc_like_cxx is true, the warnings are added to the compilation options
# when we are in BUILD mode (hence the generator expression BUILD_INTERFACE;
# if not in BUILD, such as when someone just wants the installed project,
# the generator returns an empty string).
# target_compile_options(${PROJECT_NAME}_compiler_flags INTERFACE
#   "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wunused>>"
#   "$<${msvc_cxx}:-W3>")
target_compile_options(${PROJECT_NAME}_compiler_flags INTERFACE
  "$<BUILD_INTERFACE:-Wall;-Wunused>")

# Link external libraries
target_link_libraries(${PROJECT_NAME}_compiler_flags
    INTERFACE GSL::gsl)

# Define the library
add_library(orbitsolver)

# Process the include directory
# This will set the header files for the library
add_subdirectory(include/orbitsolver)

# Process the src directory
# This will create the library
add_subdirectory(src)

# The app directory for executables
add_subdirectory(app)
