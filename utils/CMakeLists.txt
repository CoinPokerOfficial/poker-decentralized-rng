cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGUtils
        LANGUAGES CXX
        VERSION 1.0.0)

add_library(Utils STATIC # this lib is always static
        src/keccak.cpp
        src/sfmt.cpp)

add_library(DecentralizedRNG::Utils ALIAS Utils)

include(GNUInstallDirs)
target_include_directories(Utils
        PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(Utils
        PUBLIC cxx_auto_type)

set_target_properties(Utils
        PROPERTIES
            POSITION_INDEPENDENT_CODE ON
            OUTPUT_NAME "DecentralizedRNGUtils")

target_compile_definitions(Utils
        PRIVATE SFMT_MEXP=19937)


#=============== setup installation =======================
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGUtilsConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS Utils
        EXPORT UtilsTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT UtilsTargets
        FILE "DecentralizedRNGUtilsConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGUtils)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGUtilsConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGUtils)
install(DIRECTORY include/decentralized_rng
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
