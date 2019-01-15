cmake_minimum_required(VERSION 3.3)
project(PokerHandRNG
        LANGUAGES CXX
        VERSION 1.0.0)

find_package(DecentralizedRNGUtils REQUIRED)
find_package(DecentralizedRNGHandInterface REQUIRED)

add_library(PokerHandRNG SHARED
        main.cpp)
target_compile_features(PokerHandRNG
        PUBLIC cxx_auto_type cxx_lambdas)
set_target_properties(PokerHandRNG PROPERTIES
        POSITION_INDEPENDENT_CODE ON)
target_link_libraries(PokerHandRNG
        PRIVATE DecentralizedRNG::Utils DecentralizedRNG::HandInterface)

