# Collect source files using regex patterns
collect_cpp_sources("${CMAKE_CURRENT_SOURCE_DIR}" CORE_CPP_SOURCES)
collect_cuda_sources("${CMAKE_CURRENT_SOURCE_DIR}" CORE_CUDA_SOURCES)

# Create core library target
if (CERYS_USE_CUDA)
    add_library(cerys_core_for_test STATIC ${CORE_CPP_SOURCES} ${CORE_CUDA_SOURCES})
else ()
    add_library(cerys_core_for_test STATIC ${CORE_CPP_SOURCES})
endif ()

include_directories(${PROJECT_SOURCE_DIR}/src/core/include)

# Set include directories
target_include_directories(cerys_core_for_test
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/core/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Apply architecture configuration
apply_architecture_to_target(cerys_core_for_test)

# Configure x86 SIMD if applicable
configure_x86_simd(cerys_core_for_test)

# Link system libraries
link_system_libraries(cerys_core_for_test)

# Link CUDA if enabled
link_cuda_libraries(cerys_core_for_test)
