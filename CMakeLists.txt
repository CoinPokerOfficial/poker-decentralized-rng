cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNG)

# make find_package no op, for projects that are built as subprojects
# this allows to work on each project separately
set(as_subproject DecentralizedRNGUtils DecentralizedRNGHandInterface DecentralizedRNGAwardInterface)
macro(find_package)
    if(NOT "${ARGV0}" IN_LIST as_subproject)
        _find_package(${ARGV})
    endif()
endmacro()

add_subdirectory(decentralized_rng_utils)
add_subdirectory(decentralized_rng_hand_interface)
add_subdirectory(decentralized_rng_award_interface)
add_subdirectory(poker_hand_rng)
add_subdirectory(poker_award_rng)
