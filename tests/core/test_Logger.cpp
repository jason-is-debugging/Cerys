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
#include "utils/Logger.h"

#include <gtest/gtest.h>
#include <sstream>

namespace cerys::core::utils::test {

// =============================================================================
// formattedLogLevelName Tests
// =============================================================================

class FormattedLogLevelNameTest : public ::testing::Test {};

TEST_F(FormattedLogLevelNameTest, DebugLevel_ReturnsCorrectString) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Debug), "DEBUG");
}

TEST_F(FormattedLogLevelNameTest, InfoLevel_ReturnsCorrectString) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Info), "INFO ");
}

TEST_F(FormattedLogLevelNameTest, WarnLevel_ReturnsCorrectString) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Warn), "WARN ");
}

TEST_F(FormattedLogLevelNameTest, ErrorLevel_ReturnsCorrectString) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Error), "ERROR");
}

TEST_F(FormattedLogLevelNameTest, FatalLevel_ReturnsCorrectString) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Fatal), "FATAL");
}

// =============================================================================
// detail::appendToStream Tests
// =============================================================================

class AppendToStreamTest : public ::testing::Test {};

TEST_F(AppendToStreamTest, AppendsInt) {
    std::ostringstream os;
    detail::appendToStream(os, 42);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(AppendToStreamTest, AppendsString) {
    std::ostringstream os;
    detail::appendToStream(os, std::string("hello"));
    EXPECT_EQ(os.str(), "hello");
}

TEST_F(AppendToStreamTest, AppendsConstChar) {
    std::ostringstream os;
    detail::appendToStream(os, "world");
    EXPECT_EQ(os.str(), "world");
}

TEST_F(AppendToStreamTest, AppendsDouble) {
    std::ostringstream os;
    detail::appendToStream(os, 3.14);
    EXPECT_EQ(os.str(), "3.14");
}

// =============================================================================
// detail::appendAllToStream Tests
// =============================================================================

class AppendAllToStreamTest : public ::testing::Test {};

TEST_F(AppendAllToStreamTest, ZeroArgs_DoesNothing) {
    std::ostringstream os;
    detail::appendAllToStream(os);
    EXPECT_TRUE(os.str().empty());
}

TEST_F(AppendAllToStreamTest, OneArg_AppendsCorrectly) {
    std::ostringstream os;
    detail::appendAllToStream(os, 123);
    EXPECT_EQ(os.str(), "123");
}

TEST_F(AppendAllToStreamTest, TwoArgs_AppendsBoth) {
    std::ostringstream os;
    detail::appendAllToStream(os, "a", "b");
    EXPECT_EQ(os.str(), "ab");
}

TEST_F(AppendAllToStreamTest, MultipleArgs_AppendsInOrder) {
    std::ostringstream os;
    detail::appendAllToStream(os, 1, "two", 3.0);
    EXPECT_EQ(os.str(), "1two3");
}

// =============================================================================
// detail::concatToString Tests
// =============================================================================

class ConcatToStringTest : public ::testing::Test {};

TEST_F(ConcatToStringTest, ZeroArgs_ReturnsEmpty) {
    EXPECT_EQ(detail::concatToString(), "");
}

TEST_F(ConcatToStringTest, OneIntArg_ReturnsNumberString) {
    EXPECT_EQ(detail::concatToString(42), "42");
}

TEST_F(ConcatToStringTest, MultipleArgs_Concatenates) {
    EXPECT_EQ(detail::concatToString("hello", 123, "world"), "hello123world");
}

TEST_F(ConcatToStringTest, MixedTypes_ConcatenatesCorrectly) {
    EXPECT_EQ(detail::concatToString("x=", 1.5, ", y=", 2), "x=1.5, y=2");
}

// =============================================================================
// Logger Class Tests
// =============================================================================

class LoggerTest : public ::testing::Test {
protected:
    Logger logger;
    std::ostringstream output_stream;
};

TEST_F(LoggerTest, DefaultConstructor_SetsMinLevelToInfo) {
    Logger default_logger;
    EXPECT_EQ(default_logger.getMinLevel(), LogLevel::Info);
}

TEST_F(LoggerTest, SetAndGetMinLevel_WorksCorrectly) {
    logger.setMinLevel(LogLevel::Debug);
    EXPECT_EQ(logger.getMinLevel(), LogLevel::Debug);

    logger.setMinLevel(LogLevel::Error);
    EXPECT_EQ(logger.getMinLevel(), LogLevel::Error);

    logger.setMinLevel(LogLevel::Fatal);
    EXPECT_EQ(logger.getMinLevel(), LogLevel::Fatal);
}

TEST_F(LoggerTest, LogAtInfoLevel_OutputsToDefaultStream) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Debug);

    logger.log(LogLevel::Info, "test message");

    EXPECT_TRUE(capture.str().find("[INFO ] test message") != std::string::npos);
}

TEST_F(LoggerTest, LogAtDebugLevel_OutputsWhenMinIsDebug) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Debug);

    logger.log(LogLevel::Debug, "debug message");

    EXPECT_TRUE(capture.str().find("[DEBUG] debug message") != std::string::npos);
}

TEST_F(LoggerTest, LogAtWarnLevel_OutputsWhenMinIsWarn) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Warn);

    logger.log(LogLevel::Warn, "warning message");

    EXPECT_TRUE(capture.str().find("[WARN ] warning message") != std::string::npos);
}

TEST_F(LoggerTest, LogAtErrorLevel_OutputsWhenMinIsError) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Error);

    logger.log(LogLevel::Error, "error message");

    EXPECT_TRUE(capture.str().find("[ERROR] error message") != std::string::npos);
}

TEST_F(LoggerTest, LogAtFatalLevel_OutputsWhenMinIsFatal) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Fatal);

    logger.log(LogLevel::Fatal, "fatal message");

    EXPECT_TRUE(capture.str().find("[FATAL] fatal message") != std::string::npos);
}

TEST_F(LoggerTest, LogDebug_BlockedWhenMinLevelIsInfo) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Info);

    logger.log(LogLevel::Debug, "should not appear");

    EXPECT_TRUE(capture.str().empty());
}

TEST_F(LoggerTest, LogInfo_BlockedWhenMinLevelIsWarn) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Warn);

    logger.log(LogLevel::Info, "should not appear");

    EXPECT_TRUE(capture.str().empty());
}

TEST_F(LoggerTest, LogWarn_BlockedWhenMinLevelIsError) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Error);

    logger.log(LogLevel::Warn, "should not appear");

    EXPECT_TRUE(capture.str().empty());
}

TEST_F(LoggerTest, LogError_BlockedWhenMinLevelIsFatal) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Fatal);

    logger.log(LogLevel::Error, "should not appear");

    EXPECT_TRUE(capture.str().empty());
}

TEST_F(LoggerTest, LogWithMultipleArgs_ConcatenatesCorrectly) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Debug);

    logger.log(LogLevel::Info, "values: ", 1, ", ", 2, ", ", 3);

    EXPECT_TRUE(capture.str().find("[INFO ] values: 1, 2, 3") != std::string::npos);
}

TEST_F(LoggerTest, LogWithNoArgs_OutputsOnlyLevelPrefix) {
    std::ostringstream capture;
    logger.setOutput(capture);
    logger.setMinLevel(LogLevel::Debug);

    logger.log(LogLevel::Info);

    EXPECT_TRUE(capture.str().find("[INFO ]") != std::string::npos);
}

TEST_F(LoggerTest, LogWithNullOutput_DoesNotCrash) {
    logger.setOutput(*static_cast<std::ostream*>(nullptr));
    logger.setMinLevel(LogLevel::Debug);

    EXPECT_NO_THROW(logger.log(LogLevel::Debug, "test"));
}

TEST_F(LoggerTest, SetOutput_ChangesOutputStream) {
    std::ostringstream stream1, stream2;
    logger.setOutput(stream1);
    logger.setMinLevel(LogLevel::Debug);
    logger.log(LogLevel::Info, "msg1");

    logger.setOutput(stream2);
    logger.log(LogLevel::Info, "msg2");

    EXPECT_TRUE(stream1.str().find("msg1") != std::string::npos);
    EXPECT_TRUE(stream2.str().find("msg2") != std::string::npos);
    EXPECT_TRUE(stream1.str().find("msg2") == std::string::npos);
}

// =============================================================================
// Free Function Tests
// =============================================================================

class FreeFunctionTest : public ::testing::Test {
protected:
    void SetUp() override {
        setOutput(output_stream);
        setMinLevel(LogLevel::Debug);
    }

    void TearDown() override {
        setOutput(std::cout);
        setMinLevel(LogLevel::Info);
    }

    std::ostringstream output_stream;
};

TEST_F(FreeFunctionTest, DebugFunction_LogsAtDebugLevel) {
    debug("debug msg");
    EXPECT_TRUE(output_stream.str().find("[DEBUG] debug msg") != std::string::npos);
}

TEST_F(FreeFunctionTest, InfoFunction_LogsAtInfoLevel) {
    info("info msg");
    EXPECT_TRUE(output_stream.str().find("[INFO ] info msg") != std::string::npos);
}

TEST_F(FreeFunctionTest, WarnFunction_LogsAtWarnLevel) {
    warn("warn msg");
    EXPECT_TRUE(output_stream.str().find("[WARN ] warn msg") != std::string::npos);
}

TEST_F(FreeFunctionTest, ErrorFunction_LogsAtErrorLevel) {
    error("error msg");
    EXPECT_TRUE(output_stream.str().find("[ERROR] error msg") != std::string::npos);
}

TEST_F(FreeFunctionTest, FatalFunction_LogsAtFatalLevel) {
    fatal("fatal msg");
    EXPECT_TRUE(output_stream.str().find("[FATAL] fatal msg") != std::string::npos);
}

TEST_F(FreeFunctionTest, SetMinLevel_AffectsGlobalLogger) {
    setMinLevel(LogLevel::Error);
    error("error msg");
    debug("should not appear");

    EXPECT_TRUE(output_stream.str().find("error msg") != std::string::npos);
    EXPECT_TRUE(output_stream.str().find("should not appear") == std::string::npos);
}

TEST_F(FreeFunctionTest, SetOutput_AffectsGlobalLogger) {
    std::ostringstream stream2;
    setOutput(stream2);
    info("in stream2");

    EXPECT_TRUE(stream2.str().find("in stream2") != std::string::npos);
    EXPECT_TRUE(output_stream.str().find("in stream2") == std::string::npos);

    setOutput(output_stream);
}

TEST_F(FreeFunctionTest, FreeFunctionsWithMultipleArgs) {
    info("a=", 1, " b=", 2, " c=", 3);
    EXPECT_TRUE(output_stream.str().find("a=1 b=2 c=3") != std::string::npos);
}

} // namespace cerys::core::utils::test
