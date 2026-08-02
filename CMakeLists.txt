cmake_minimum_required(VERSION 3.20)
if (MSVC)
    add_compile_options("/execution_charset:utf-8" "/source_charset:utf-8")
    set(ENV{VSLANG} "1033")
endif ()


#=========================== Project Configuration ===================================
project(cerys
        VERSION 0.0.1
        LANGUAGES CXX
)

include(GNUInstallDirs)

# Include custom CMake modules from cmake/ directory
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Load CMake modules
include(CompilerConfig)
include(Architecture)
include(CollectSources)
include(TargetArchitecture)
include(SimdConfig)
include(LinkLibraries)

#=========================== Dependencies Management ===================================
# ---- vcpkg toolchain detection ----

# =========================== Main Library Aggregation ===================================
# Include all source subdirectories which will create their respective targets
add_subdirectory(src)

# Create an alias for the main library (using core as the primary interface)
add_library(cerys::cerys ALIAS cerys_core)

# =========================== Install Configuration ===================================
# Install core library
install(TARGETS cerys_core
        EXPORT cerysTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY "${PROJECT_SOURCE_DIR}/core/include/"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT cerysTargets
        NAMESPACE h3::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/cerys"
)

# =========================== Tests Configuration ===================================
# Include test subdirectories
add_subdirectory(tests)
