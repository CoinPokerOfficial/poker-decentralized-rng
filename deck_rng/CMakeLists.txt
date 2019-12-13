cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNGDeckRNG
        LANGUAGES CXX
        VERSION 1.0.0)

find_package(DecentralizedRNGUtils REQUIRED)
find_package(DecentralizedRNGDeckInterface REQUIRED)

add_library(DeckRNG main.cpp)
add_library(DecentralizedRNG::DeckRNG ALIAS DeckRNG)

get_target_property(LIB_TYPE DeckRNG TYPE)
if (LIB_TYPE STREQUAL "SHARED_LIBRARY")
    target_compile_definitions(DeckRNG PUBLIC
            $<BUILD_INTERFACE:DECKRNGLIB_SHARED_EXPORTS>
            $<INSTALL_INTERFACE:DECKRNGLIB_SHARED_IMPORTS>)
    set_target_properties(DeckRNG PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

target_compile_features(DeckRNG
        PUBLIC cxx_auto_type cxx_lambdas)
target_link_libraries(DeckRNG
        PRIVATE DecentralizedRNG::Utils
        PUBLIC DecentralizedRNG::DeckInterface)

#=============== setup installation =======================
include(GNUInstallDirs)
ApplyInstallPackagePrefix(DecentralizedRNGDeckRNG)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGDeckRNGConfigVersion.cmake
        COMPATIBILITY SameMajorVersion)
install(TARGETS DeckRNG
        EXPORT DeckRNGTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(EXPORT DeckRNGTargets
        FILE "DecentralizedRNGDeckRNGConfig.cmake"
        NAMESPACE DecentralizedRNG::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGDeckRNG)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DecentralizedRNGDeckRNGConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/DecentralizedRNGDeckRNG)
