## CMakeLists for source files
# Adds the CPP files to the library

# Include the header directory for those who use the library
target_include_directories(orbitsolver PUBLIC "${PROJECT_SOURCE_DIR}/include")

# Attach the source files to the library
# Source files are private as codes using the library don't need them
target_sources(orbitsolver
    PRIVATE 
        io.cpp
        orbits.cpp
)

# Link the project settings to the library
target_link_libraries(orbitsolver PUBLIC ${PROJECT_NAME}_compiler_flags)

install(TARGETS orbitsolver LIBRARY)