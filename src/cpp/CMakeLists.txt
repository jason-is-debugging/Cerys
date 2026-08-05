# Core ML Library CMakeLists.txt
# This is the main part of the ML library containing core implementations

# Collect source files using regex patterns
collect_cpp_sources("${CMAKE_CURRENT_SOURCE_DIR}" CPP_FRONTEND_SOURCES)
collect_cuda_sources("${CMAKE_CURRENT_SOURCE_DIR}" CPP_FRONTEND_CUDA_SOURCES)

# Create core library target
if (CERYS_USE_CUDA)
    add_library(cerys_cpp_frontend STATIC ${CPP_FRONTEND_SOURCES} ${CPP_FRONTEND_CUDA_SOURCES})
else ()
    add_library(cerys_cpp_frontend STATIC ${CPP_FRONTEND_SOURCES})
endif ()

include_directories(${PROJECT_SOURCE_DIR}/src/cpp/include)

# Set include directories
target_include_directories(cerys_cpp_frontend
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/cpp/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# Apply architecture configuration
apply_architecture_to_target(cerys_cpp_frontend)

# Configure x86 SIMD if applicable
configure_x86_simd(cerys_cpp_frontend)

# Link system libraries
link_system_libraries(cerys_cpp_frontend)

# Link CUDA if enabled
link_cuda_libraries(cerys_cpp_frontend)
