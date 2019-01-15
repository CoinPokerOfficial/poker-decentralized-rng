cmake_minimum_required(VERSION 3.3)
project(PokerAwardRNG
        LANGUAGES CXX
        VERSION 1.0.0)

find_package(DecentralizedRNGUtils REQUIRED)
find_package(DecentralizedRNGAwardInterface REQUIRED)

add_library(PokerAwardRNG SHARED
        main.cpp)
target_compile_features(PokerAwardRNG
        PUBLIC cxx_auto_type cxx_lambdas)
set_target_properties(PokerAwardRNG PROPERTIES
        POSITION_INDEPENDENT_CODE ON)
target_link_libraries(PokerAwardRNG
        PRIVATE DecentralizedRNG::Utils DecentralizedRNG::AwardInterface)

