//  Copyright (c) 2026-2026 Contributors of Cerys(https://github.com/jason-is-debugging/Cerys)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       https://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Contributors:
//  Jason Shen (jason.shen.gm@gmail.com) (https://github.com/jason-is-debugging)
//
#ifndef CERYS_EXCEPTION_D150FB88B26F4F91A69FA8EF0C55BE43_H
#define CERYS_EXCEPTION_D150FB88B26F4F91A69FA8EF0C55BE43_H
#include <format>

namespace std {
class runtime_error;
}

namespace cerys::core::utils {
template <typename ExceptionType = std::runtime_error, typename... Args>
[[noreturn]] void throwWithFmt(std::format_string<Args...> fmt, Args&&... args) {
    throw ExceptionType(std::format(fmt, std::forward<Args>(args)...));
}

template <typename... Args>
[[noreturn]] void throwRuntime(std::format_string<Args...> fmt, Args&&... args) {
    throw std::runtime_error(std::format(fmt, std::forward<Args>(args)...));
}

}

#endif //CERYS_EXCEPTION_D150FB88B26F4F91A69FA8EF0C55BE43_H