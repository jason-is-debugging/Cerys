#  Copyright (c) 2026-2026 Contributors of Cerys(https://github.com/jason-is-debugging/Cerys)
#
#  Licensed under the Apache License, Version 2.0 (the "License");
#  you may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#       https://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#
#  Contributors:
#  Jason Shen (jason.shen.gm@gmail.com) (https://github.com/jason-is-debugging)
#

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Collect all test source files
file(GLOB_RECURSE CORE_TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/utils/*.cpp"
)

# Create test executable
add_executable(core_tests ${CORE_TEST_SOURCES})

# Include test main
target_sources(core_tests PRIVATE "${CMAKE_SOURCE_DIR}/tests/test_main.cpp")

# Link with GoogleTest only (tests are header-only utilities)
target_link_libraries(core_tests
    PRIVATE
    GTest::gtest GTest::gtest_main
)

# Enable C++17
target_compile_features(core_tests PRIVATE cxx_std_17)

# Define this when building tests so that test-only members are available
target_compile_definitions(core_tests PRIVATE CERYS_TESTING)

# Add include directories for headers
target_include_directories(core_tests PRIVATE
    "${CMAKE_SOURCE_DIR}/src/core/include"
)

# Add coverage support if enabled
if(CERYS_COVERAGE)
    target_compile_options(core_tests PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:
            -fprofile-arcs -ftest-coverage -O0 -g>
    )
    target_link_options(core_tests PRIVATE
        $<$<CXX_COMPILER_ID:GNU,Clang>:
            -fprofile-arcs -ftest-coverage>
    )
endif()

# Register tests with CTest
include(GoogleTest)
gtest_discover_tests(core_tests)
