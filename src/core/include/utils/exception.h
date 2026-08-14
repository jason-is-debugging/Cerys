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

#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

namespace cerys::core::utils {

namespace detail {

// Append any streamable value to the buffer. Used by the throw* helpers below.
template <typename T>
inline void appendToStream(std::ostringstream& os, T&& value) {
    os << std::forward<T>(value);
}

inline void appendAllToStream(std::ostringstream&) {}

template <typename First, typename... Rest>
inline void appendAllToStream(std::ostringstream& os, First&& first, Rest&&... rest) {
    appendToStream(os, std::forward<First>(first));
    appendAllToStream(os, std::forward<Rest>(rest)...);
}

template <typename... Args>
inline std::string concatToString(Args&&... args) {
    std::ostringstream os;
    appendAllToStream(os, std::forward<Args>(args)...);
    return os.str();
}

} // namespace detail

// Throw an exception of `ExceptionType` constructed from the concatenation
// of all `args`. `args` may be any type that supports `operator<<` with
// `std::ostringstream` (numbers, strings, STL containers with operator<<, etc.).
template <typename ExceptionType = std::runtime_error, typename... Args>
[[noreturn]] inline void throwWithFmt(Args&&... args) {
    throw ExceptionType(detail::concatToString(std::forward<Args>(args)...));
}

// Shortcut: throw std::runtime_error from concatenated args.
template <typename... Args>
[[noreturn]] inline void throwRuntime(Args&&... args) {
    throw std::runtime_error(detail::concatToString(std::forward<Args>(args)...));
}

// Shortcut: throw std::invalid_argument from concatenated args.
template <typename... Args>
[[noreturn]] inline void throwInvalidArg(Args&&... args) {
    throw std::invalid_argument(detail::concatToString(std::forward<Args>(args)...));
}

// Shortcut: throw std::out_of_range from concatenated args.
template <typename... Args>
[[noreturn]] inline void throwOutOfRange(Args&&... args) {
    throw std::out_of_range(detail::concatToString(std::forward<Args>(args)...));
}

// Shortcut: throw std::logic_error from concatenated args.
template <typename... Args>
[[noreturn]] inline void throwLogic(Args&&... args) {
    throw std::logic_error(detail::concatToString(std::forward<Args>(args)...));
}

} // namespace cerys::core::utils

#endif // CERYS_EXCEPTION_D150FB88B26F4F91A69FA8EF0C55BE43_H
