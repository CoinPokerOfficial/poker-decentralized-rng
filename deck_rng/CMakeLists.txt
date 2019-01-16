cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGDeckRNG
        LANGUAGES CXX
        VERSION 1.0.0)

find_package(DecentralizedRNGUtils REQUIRED)
find_package(DecentralizedRNGDeckInterface REQUIRED)

add_library(DeckRNG main.cpp)
add_library(DecentralizedRNG::DeckRNG ALIAS DeckRNG)

target_compile_features(DeckRNG
        PUBLIC cxx_auto_type cxx_lambdas)
set_target_properties(DeckRNG PROPERTIES
        POSITION_INDEPENDENT_CODE ON)
target_link_libraries(DeckRNG
        PUBLIC DecentralizedRNG::Utils DecentralizedRNG::DeckInterface)

#=============== setup installation =======================
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGDeckRNGConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS DeckRNG
        EXPORT DeckRNGTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT DeckRNGTargets
        FILE "DecentralizedRNGDeckRNGConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGDeckRNG)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGDeckRNGConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGDeckRNG)
