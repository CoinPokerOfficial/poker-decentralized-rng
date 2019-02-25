cmake_minimum_required(VERSION 3.3)
project(DecentralizedRNG)

# make find_package no op, for projects that are built as subprojects
# this allows to work on each project separately
set(as_subproject DecentralizedRNGUtils DecentralizedRNGDeckInterface DecentralizedRNGAwardInterface)
macro(find_package)
    if(NOT "${ARGV0}" IN_LIST as_subproject)
        _find_package(${ARGV})
    endif()
endmacro()


# this will allow to install packages to separate root directories, this search path is available since cmake 3.7
# <prefix>/<name>*/(lib/<arch>|lib|share)/cmake/<name>*/          (W/U)
# <prefix>/<name>*/(lib/<arch>|lib|share)/<name>*/                (W/U)
# <prefix>/<name>*/(lib/<arch>|lib|share)/<name>*/(cmake|CMake)/  (W/U)
option(INSTALL_WITH_PACKAGE_PREFIX "instead of using default folders for installation, all packages will be prefixed with package name" OFF)
macro(ApplyInstallPackagePrefix PackageName)
    if (INSTALL_WITH_PACKAGE_PREFIX)
        set(CMAKE_INSTALL_INCLUDEDIR "${PackageName}/${CMAKE_INSTALL_INCLUDEDIR}")
        set(CMAKE_INSTALL_LIBDIR "${PackageName}/${CMAKE_INSTALL_LIBDIR}")
        set(CMAKE_INSTALL_BINDIR "${PackageName}/${CMAKE_INSTALL_BINDIR}")
    endif()
endmacro()

add_subdirectory(utils)
add_subdirectory(deck_interface)
add_subdirectory(award_interface)
add_subdirectory(deck_rng)
add_subdirectory(award_rng)
