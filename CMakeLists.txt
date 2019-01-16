cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNG)

# make find_package no op, for projects that are built as subprojects
# this allows to work on each project separately
set(as_subproject DecentralizedRNGUtils DecentralizedRNGDeckInterface DecentralizedRNGAwardInterface)
macro(find_package)
    if(NOT "${ARGV0}" IN_LIST as_subproject)
        _find_package(${ARGV})
    endif()
endmacro()

add_subdirectory(utils)
add_subdirectory(deck_interface)
add_subdirectory(award_interface)
add_subdirectory(deck_rng)
add_subdirectory(award_rng)
