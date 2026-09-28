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

#ifndef CERYS_LOGGER_F00E7D11B6A04FFA8E2F9C5D3A77B14C_H
#define CERYS_LOGGER_F00E7D11B6A04FFA8E2F9C5D3A77B14C_H

#include <iostream>
#include <mutex>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

#include "exception.h"

namespace cerys::core::utils {

enum class LogLevel {
    Debug = 0,
    Info = 1,
    Warn = 2,
    Error = 3,
    Fatal = 4
};

inline const char* formattedLogLevelName(const LogLevel level) {
    switch (level) {
    case LogLevel::Debug:
        return "DEBUG";
    case LogLevel::Info:
        return "INFO ";
    case LogLevel::Warn:
        return "WARN ";
    case LogLevel::Error:
        return "ERROR";
    case LogLevel::Fatal:
        return "FATAL";
    }
    return "?"; // LCOV_EXCL_LINE
}

namespace logger_detail {

template <typename T>
inline void appendToStream(std::ostringstream& os, T&& value) {
    os << std::forward<T>(value);
}

inline void appendAllToStream(std::ostringstream&) {
}

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

} // namespace logger_detail

class Logger {
public:
    Logger() = default;

    Logger(const Logger&) = delete;

    Logger& operator=(const Logger&) = delete;

    void setMinLevel(const LogLevel level) noexcept {
        std::lock_guard lock(mMutex);
        mMinLevel = level;
    }

    [[nodiscard]] LogLevel getMinLevel() const noexcept {
        std::lock_guard lock(mMutex);
        return mMinLevel;
    }

    void setOutput(std::ostream& out) noexcept {
        std::lock_guard lock(mMutex);
        mOut = &out;
    }

#ifdef CERYS_TESTING
    // Test-only overload: allows setting mOut to nullptr to verify the guard branch.
    void setOutput(std::ostream* out) noexcept {
        std::lock_guard lock(mMutex);
        mOut = out;
    }
#endif

    template <typename... Args>
    void log(LogLevel level, Args&&... args) {
        const std::string message = logger_detail::concatToString(std::forward<Args>(args)...);
        std::lock_guard lock(mMutex);
        if (static_cast<int>(level) < static_cast<int>(mMinLevel)) {
            return; // LCOV_EXCL_LINE
        }
        if (mOut == nullptr) {
            throwRuntime("Logger output is not set"); // LCOV_EXCL_LINE
        }
        *mOut << '[' << formattedLogLevelName(level) << "] " << message << '\n';
        mOut->flush();
    }

private:
    mutable std::mutex mMutex;
    LogLevel mMinLevel = LogLevel::Info;
    std::ostream* mOut = &std::cout;
};

// Process-wide logger instance. Defined in the header so the free functions
// below can use it without a separate .cpp file. Meyers-singleton style.
inline Logger& logger() {
    static Logger instance;
    return instance;
}

// Free-function logging API. Callers write `utils::info(...)` instead of
// reaching for a global instance.
template <typename... Args>
inline void debug(Args&&... args) {
    logger().log(LogLevel::Debug, std::forward<Args>(args)...);
}

template <typename... Args>
inline void info(Args&&... args) {
    logger().log(LogLevel::Info, std::forward<Args>(args)...);
}

template <typename... Args>
inline void warn(Args&&... args) {
    logger().log(LogLevel::Warn, std::forward<Args>(args)...);
}

template <typename... Args>
inline void error(Args&&... args) {
    logger().log(LogLevel::Error, std::forward<Args>(args)...);
}

template <typename... Args>
inline void fatal(Args&&... args) {
    logger().log(LogLevel::Fatal, std::forward<Args>(args)...);
}

inline void setMinLevel(const LogLevel level) {
    logger().setMinLevel(level);
}

inline void setOutput(std::ostream& out) {
    logger().setOutput(out);
}

} // namespace cerys::core::utils

#endif // CERYS_LOGGER_F00E7D11B6A04FFA8E2F9C5D3A77B14C_H
