cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGHandInterface
        LANGUAGES CXX
        VERSION 1.0.0)

add_library(HandInterface INTERFACE)
add_library(DecentralizedRNG::HandInterface ALIAS HandInterface)

include(GNUInstallDirs)
target_include_directories(HandInterface INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#=============== setup installation =======================
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGHandInterfaceConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS HandInterface
        EXPORT HandInterfaceTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT HandInterfaceTargets
        FILE "DecentralizedRNGHandInterfaceConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGHandInterface)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGHandInterfaceConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGHandInterface)
install(DIRECTORY include/decentralized_rng
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
