#==============================================================================
# nfx-cpu - Top-level CMake configuration
#==============================================================================

#----------------------------------------------
# Project definition
#----------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(nfx-cpu
	VERSION 0.1.3
	DESCRIPTION "Cross-platform C++ CPU feature detection and system identification library"
	HOMEPAGE_URL "https://github.com/nfx-libs/nfx-cpu"
	LANGUAGES CXX
)

#----------------------------------------------
# Version configuration
#----------------------------------------------

set(NFX_CPU_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE INTERNAL "nfx-cpu major version")
set(NFX_CPU_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE INTERNAL "nfx-cpu minor version")
set(NFX_CPU_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE INTERNAL "nfx-cpu patch version")
set(NFX_CPU_VERSION       ${PROJECT_VERSION}       CACHE INTERNAL "nfx-cpu version")

#----------------------------------------------
# Testing setup
#----------------------------------------------

enable_testing()

#----------------------------------------------
# Build options
#----------------------------------------------

# --- Build components (header-only library) ---
option(NFX_CPU_BUILD_TESTS          "Build tests"                         OFF )
option(NFX_CPU_BUILD_SAMPLES        "Build samples"                       OFF )
option(NFX_CPU_BUILD_BENCHMARKS     "Build benchmarks"                    OFF )
option(NFX_CPU_BUILD_DOCUMENTATION  "Build Doxygen documentation"         OFF )

# --- Installation ---
option(NFX_CPU_INSTALL_PROJECT      "Install project"                     OFF )

# --- Packaging ---
option(NFX_CPU_PACKAGE_SOURCE       "Enable source package generation"    OFF )
option(NFX_CPU_PACKAGE_ARCHIVE      "Enable TGZ/ZIP package generation"   OFF )
option(NFX_CPU_PACKAGE_DEB          "Enable DEB package generation"       OFF )
option(NFX_CPU_PACKAGE_RPM          "Enable RPM package generation"       OFF )
option(NFX_CPU_PACKAGE_WIX          "Enable WiX Windows installer (MSI)"  OFF )

#----------------------------------------------
# CMake modules configuration
#----------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#----------------------------------------------
# Main configuration
#----------------------------------------------

include(nfxCpuBuildConfig)
include(nfxCpuDependencies)
include(nfxCpuTarget)

#----------------------------------------------
# Installation and packaging
#----------------------------------------------

include(nfxCpuInstall)
include(nfxCpuPackaging)

#----------------------------------------------
# Targets
#----------------------------------------------

add_subdirectory(test)
add_subdirectory(samples)
add_subdirectory(benchmark)
add_subdirectory(doc)
