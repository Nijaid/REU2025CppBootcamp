target_sources(orbitsolver
    PUBLIC FILE_SET HEADERS
    BASE_DIRS "${PROJECT_SOURCE_DIR}/include"
    FILES 
        orbitutils.hpp
        io.hpp
        orbits.hpp
)