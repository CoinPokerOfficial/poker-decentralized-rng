cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGAwardRNG
        LANGUAGES CXX
        VERSION 1.0.0)

find_package(DecentralizedRNGUtils REQUIRED)
find_package(DecentralizedRNGAwardInterface REQUIRED)

add_library(AwardRNG main.cpp)
add_library(DecentralizedRNG::AwardRNG ALIAS AwardRNG)

get_target_property(LIB_TYPE AwardRNG TYPE)
if (LIB_TYPE STREQUAL "SHARED_LIBRARY")
	target_compile_definitions(AwardRNG PUBLIC
            $<BUILD_INTERFACE:AWARDRNGLIB_SHARED_EXPORTS>
            $<INSTALL_INTERFACE:AWARDRNGLIB_SHARED_IMPORTS>)
endif()

target_compile_features(AwardRNG
        PUBLIC cxx_auto_type cxx_lambdas)
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
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT AwardRNGTargets
        FILE "DecentralizedRNGAwardRNGConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGAwardRNG)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGAwardRNGConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGAwardRNG)
