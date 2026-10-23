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


# Include source directories for headers
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/src/cpp/include)
include_directories(${CMAKE_SOURCE_DIR}/src/core/include)

add_executable(tensor_basic_usage_example
    tensor_basic_usage.cpp
    ${CMAKE_SOURCE_DIR}/src/cpp/src/Tensor.cpp
)

# Link the core library (if available from main build)
if(TARGET cerys::core)
    target_link_libraries(tensor_basic_usage_example PRIVATE cerys::core)
elseif(EXISTS ${CMAKE_SOURCE_DIR}/build/src/core/libcerys_core.a)
    target_link_libraries(tensor_basic_usage_example PRIVATE
        ${CMAKE_SOURCE_DIR}/build/src/core/libcerys_core.a)
endif()
