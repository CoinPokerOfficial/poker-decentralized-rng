cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGAwardInterface
        LANGUAGES CXX
        VERSION 1.0.0)

add_library(AwardInterface INTERFACE)
add_library(DecentralizedRNG::AwardInterface ALIAS AwardInterface)

include(GNUInstallDirs)
target_include_directories(AwardInterface INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#=============== setup installation =======================
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGAwardInterfaceConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS AwardInterface
        EXPORT AwardInterfaceTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT AwardInterfaceTargets
        FILE "DecentralizedRNGAwardInterfaceConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGAwardInterface)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGAwardInterfaceConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGAwardInterface)
install(DIRECTORY include/decentralized_rng
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
