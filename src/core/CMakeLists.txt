# Core ML Library CMakeLists.txt
# This is the main part of the ML library containing core implementations

# Collect source files using regex patterns
collect_cpp_sources("${CMAKE_CURRENT_SOURCE_DIR}" CORE_CPP_SOURCES)
collect_cuda_sources("${CMAKE_CURRENT_SOURCE_DIR}" CORE_CUDA_SOURCES)

# Create core library target
if (CERYS_USE_CUDA)
    add_library(cerys_core STATIC ${CORE_CPP_SOURCES} ${CORE_CUDA_SOURCES})
else ()
    add_library(cerys_core STATIC ${CORE_CPP_SOURCES})
endif ()

include_directories(${PROJECT_SOURCE_DIR}/src/core/include)

add_library(cerys::core ALIAS cerys_core)

# Set include directories
target_include_directories(cerys_core
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Apply architecture configuration
apply_architecture_to_target(cerys_core)

# Configure x86 SIMD if applicable
configure_x86_simd(cerys_core)

# Link system libraries
link_system_libraries(cerys_core)

# Link CUDA if enabled
link_cuda_libraries(cerys_core)
