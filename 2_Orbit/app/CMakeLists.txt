## CMakeLists for apps
# Creates executables that use OrbitSolver

add_executable(orbitExample orbit_example.cpp)

target_link_libraries(orbitExample
    PRIVATE orbitsolver)

install(TARGETS orbitExample RUNTIME)