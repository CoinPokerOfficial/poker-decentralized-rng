cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGDeckInterface
        LANGUAGES CXX
        VERSION 1.0.0)

add_library(DeckInterface INTERFACE)
add_library(DecentralizedRNG::DeckInterface ALIAS DeckInterface)

include(GNUInstallDirs)
target_include_directories(DeckInterface INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#=============== setup installation =======================
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGDeckInterfaceConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS DeckInterface
        EXPORT DeckInterfaceTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT DeckInterfaceTargets
        FILE "DecentralizedRNGDeckInterfaceConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGDeckInterface)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGDeckInterfaceConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGDeckInterface)
install(DIRECTORY include/decentralized_rng
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
