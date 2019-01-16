cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGAwardRNG
        LANGUAGES CXX
        VERSION 1.0.0)

find_package(DecentralizedRNGUtils REQUIRED)
find_package(DecentralizedRNGAwardInterface REQUIRED)

add_library(AwardRNG main.cpp)
add_library(DecentralizedRNG::AwardRNG ALIAS AwardRNG)

target_compile_features(AwardRNG
        PUBLIC cxx_auto_type cxx_lambdas)
set_target_properties(AwardRNG PROPERTIES
        POSITION_INDEPENDENT_CODE ON)
target_link_libraries(AwardRNG
        PUBLIC DecentralizedRNG::Utils DecentralizedRNG::AwardInterface)

#=============== setup installation =======================
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGAwardRNGConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS AwardRNG
        EXPORT AwardRNGTargets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT AwardRNGTargets
        FILE "DecentralizedRNGAwardRNGConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGAwardRNG)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGAwardRNGConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGAwardRNG)
