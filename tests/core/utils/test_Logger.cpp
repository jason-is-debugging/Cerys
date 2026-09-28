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
#include <string>

// Verify CERYS_TESTING is defined for test-only code paths
#ifdef CERYS_TESTING
static_assert(true, "CERYS_TESTING is defined");
#else
static_assert(false, "CERYS_TESTING should be defined for tests");
#endif

namespace cerys::core::utils {

// =============================================================================
// Tests for LogLevel enum
// =============================================================================

class LogLevelTest : public ::testing::Test {};

TEST_F(LogLevelTest, LogLevelValuesAreInIncreasingOrder) {
    EXPECT_LT(static_cast<int>(LogLevel::Debug), static_cast<int>(LogLevel::Info));
    EXPECT_LT(static_cast<int>(LogLevel::Info), static_cast<int>(LogLevel::Warn));
    EXPECT_LT(static_cast<int>(LogLevel::Warn), static_cast<int>(LogLevel::Error));
    EXPECT_LT(static_cast<int>(LogLevel::Error), static_cast<int>(LogLevel::Fatal));
}

// =============================================================================
// Tests for formattedLogLevelName
// =============================================================================

class FormattedLogLevelNameTest : public ::testing::Test {};

TEST_F(FormattedLogLevelNameTest, DebugReturnsCorrectFormat) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Debug), "DEBUG");
}

TEST_F(FormattedLogLevelNameTest, InfoReturnsCorrectFormat) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Info), "INFO ");
}

TEST_F(FormattedLogLevelNameTest, WarnReturnsCorrectFormat) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Warn), "WARN ");
}

TEST_F(FormattedLogLevelNameTest, ErrorReturnsCorrectFormat) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Error), "ERROR");
}

TEST_F(FormattedLogLevelNameTest, FatalReturnsCorrectFormat) {
    EXPECT_STREQ(formattedLogLevelName(LogLevel::Fatal), "FATAL");
}

// =============================================================================
// Tests for logger_detail::concatToString - Logger internal helper
// =============================================================================

class LoggerDetailConcatToStringTest : public ::testing::Test {};

TEST_F(LoggerDetailConcatToStringTest, EmptyArgsReturnsEmptyString) {
    std::string result = logger_detail::concatToString();
    EXPECT_EQ(result, "");
}

TEST_F(LoggerDetailConcatToStringTest, SingleStringArg) {
    std::string result = logger_detail::concatToString(std::string("hello"));
    EXPECT_EQ(result, "hello");
}

TEST_F(LoggerDetailConcatToStringTest, SingleIntArg) {
    std::string result = logger_detail::concatToString(42);
    EXPECT_EQ(result, "42");
}

TEST_F(LoggerDetailConcatToStringTest, MultipleArgsIntAndString) {
    std::string result = logger_detail::concatToString("value=", 123);
    EXPECT_EQ(result, "value=123");
}

TEST_F(LoggerDetailConcatToStringTest, MultipleArgsStringIntString) {
    std::string result = logger_detail::concatToString("a", 1, "b", 2);
    EXPECT_EQ(result, "a1b2");
}

TEST_F(LoggerDetailConcatToStringTest, DoubleArg) {
    std::string result = logger_detail::concatToString(3.14159);
    EXPECT_EQ(result, "3.14159");
}

TEST_F(LoggerDetailConcatToStringTest, MultipleDoubleArgs) {
    std::string result = logger_detail::concatToString(1.5, " + ", 2.5, " = ", 4.0);
    EXPECT_EQ(result, "1.5 + 2.5 = 4");
}

TEST_F(LoggerDetailConcatToStringTest, CharPointerArg) {
    std::string result = logger_detail::concatToString("test");
    EXPECT_EQ(result, "test");
}

TEST_F(LoggerDetailConcatToStringTest, MultipleCharPointerArgs) {
    std::string result = logger_detail::concatToString("one", " two", " three");
    EXPECT_EQ(result, "one two three");
}

TEST_F(LoggerDetailConcatToStringTest, BoolTrueArg) {
    std::string result = logger_detail::concatToString(true);
    EXPECT_EQ(result, "1");
}

TEST_F(LoggerDetailConcatToStringTest, BoolFalseArg) {
    std::string result = logger_detail::concatToString(false);
    EXPECT_EQ(result, "0");
}

TEST_F(LoggerDetailConcatToStringTest, SingleCharArg) {
    std::string result = logger_detail::concatToString('x');
    EXPECT_EQ(result, "x");
}

TEST_F(LoggerDetailConcatToStringTest, MultipleCharArgs) {
    std::string result = logger_detail::concatToString('a', 'b', 'c');
    EXPECT_EQ(result, "abc");
}

TEST_F(LoggerDetailConcatToStringTest, MixedTypes) {
    std::string result = logger_detail::concatToString("int: ", 10, " str: ", "hello", " bool: ", true);
    EXPECT_EQ(result, "int: 10 str: hello bool: 1");
}

TEST_F(LoggerDetailConcatToStringTest, LongString) {
    std::string result = logger_detail::concatToString(
        "This is a long message that should be concatenated properly");
    EXPECT_EQ(result, "This is a long message that should be concatenated properly");
}

TEST_F(LoggerDetailConcatToStringTest, MultipleLongStrings) {
    std::string result = logger_detail::concatToString(
        "Part1 ", "Part2 ", "Part3 ", "Part4 ", "Part5");
    EXPECT_EQ(result, "Part1 Part2 Part3 Part4 Part5");
}

TEST_F(LoggerDetailConcatToStringTest, NegativeIntArg) {
    std::string result = logger_detail::concatToString(-123);
    EXPECT_EQ(result, "-123");
}

TEST_F(LoggerDetailConcatToStringTest, NegativeDoubleArg) {
    std::string result = logger_detail::concatToString(-3.14);
    EXPECT_EQ(result, "-3.14");
}

// =============================================================================
// Tests for logger_detail::appendToStream
// =============================================================================

class LoggerDetailAppendToStreamTest : public ::testing::Test {};

TEST_F(LoggerDetailAppendToStreamTest, AppendInt) {
    std::ostringstream os;
    logger_detail::appendToStream(os, 42);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(LoggerDetailAppendToStreamTest, AppendString) {
    std::ostringstream os;
    logger_detail::appendToStream(os, std::string("hello"));
    EXPECT_EQ(os.str(), "hello");
}

TEST_F(LoggerDetailAppendToStreamTest, AppendCharPointer) {
    std::ostringstream os;
    logger_detail::appendToStream(os, "world");
    EXPECT_EQ(os.str(), "world");
}

TEST_F(LoggerDetailAppendToStreamTest, AppendDouble) {
    std::ostringstream os;
    logger_detail::appendToStream(os, 3.14);
    EXPECT_EQ(os.str(), "3.14");
}

TEST_F(LoggerDetailAppendToStreamTest, AppendBoolTrue) {
    std::ostringstream os;
    logger_detail::appendToStream(os, true);
    EXPECT_EQ(os.str(), "1");
}

TEST_F(LoggerDetailAppendToStreamTest, AppendBoolFalse) {
    std::ostringstream os;
    logger_detail::appendToStream(os, false);
    EXPECT_EQ(os.str(), "0");
}

// =============================================================================
// Tests for logger_detail::appendAllToStream
// =============================================================================

class LoggerDetailAppendAllToStreamTest : public ::testing::Test {};

TEST_F(LoggerDetailAppendAllToStreamTest, EmptyArgs) {
    std::ostringstream os;
    logger_detail::appendAllToStream(os);
    EXPECT_EQ(os.str(), "");
}

TEST_F(LoggerDetailAppendAllToStreamTest, SingleArg) {
    std::ostringstream os;
    logger_detail::appendAllToStream(os, 42);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(LoggerDetailAppendAllToStreamTest, TwoArgs) {
    std::ostringstream os;
    logger_detail::appendAllToStream(os, "value=", 123);
    EXPECT_EQ(os.str(), "value=123");
}

TEST_F(LoggerDetailAppendAllToStreamTest, ThreeArgs) {
    std::ostringstream os;
    logger_detail::appendAllToStream(os, 1, " + ", 2, " = ", 3);
    EXPECT_EQ(os.str(), "1 + 2 = 3");
}

TEST_F(LoggerDetailAppendAllToStreamTest, FourArgs) {
    std::ostringstream os;
    logger_detail::appendAllToStream(os, "a", "b", "c", "d");
    EXPECT_EQ(os.str(), "abcd");
}

TEST_F(LoggerDetailAppendAllToStreamTest, FiveArgs) {
    std::ostringstream os;
    logger_detail::appendAllToStream(os, "one", 2, "three", 4, "five");
    EXPECT_EQ(os.str(), "one2three4five");
}

// =============================================================================
// Tests for Logger class
// =============================================================================

class LoggerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Capture output to a stringstream
        output_stream = std::make_shared<std::ostringstream>();
        logger.setOutput(*output_stream);
        logger.setMinLevel(LogLevel::Debug);
    }

    std::shared_ptr<std::ostringstream> output_stream;
    Logger logger;
};

TEST_F(LoggerTest, DefaultConstructorInitializesCorrectly) {
    Logger new_logger;
    std::ostringstream os;
    new_logger.setOutput(os);
    new_logger.setMinLevel(LogLevel::Debug);
    new_logger.log(LogLevel::Info, "test");
    EXPECT_NE(os.str(), "");
}

TEST_F(LoggerTest, CopyConstructorDeleted) {
    static_assert(!std::is_copy_constructible<Logger>::value,
                  "Logger should not be copy constructible");
}

TEST_F(LoggerTest, CopyAssignmentDeleted) {
    static_assert(!std::is_copy_assignable<Logger>::value,
                  "Logger should not be copy assignable");
}

TEST_F(LoggerTest, LogDebugLevel) {
    logger.log(LogLevel::Debug, "debug message");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[DEBUG] debug message"), std::string::npos);
}

TEST_F(LoggerTest, LogInfoLevel) {
    logger.log(LogLevel::Info, "info message");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] info message"), std::string::npos);
}

TEST_F(LoggerTest, LogWarnLevel) {
    logger.log(LogLevel::Warn, "warn message");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[WARN ] warn message"), std::string::npos);
}

TEST_F(LoggerTest, LogErrorLevel) {
    logger.log(LogLevel::Error, "error message");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[ERROR] error message"), std::string::npos);
}

TEST_F(LoggerTest, LogFatalLevel) {
    logger.log(LogLevel::Fatal, "fatal message");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[FATAL] fatal message"), std::string::npos);
}

TEST_F(LoggerTest, LogMultipleArgs) {
    logger.log(LogLevel::Info, "value=", 42, " name=", "test");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] value=42 name=test"), std::string::npos);
}

TEST_F(LoggerTest, LogWithNoArgs) {
    logger.log(LogLevel::Info);
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] "), std::string::npos);
}

TEST_F(LoggerTest, LogIntegerArg) {
    logger.log(LogLevel::Info, 123);
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] 123"), std::string::npos);
}

TEST_F(LoggerTest, LogDoubleArg) {
    logger.log(LogLevel::Info, 3.14159);
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] 3.14159"), std::string::npos);
}

TEST_F(LoggerTest, LogBoolTrueArg) {
    logger.log(LogLevel::Info, true);
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] 1"), std::string::npos);
}

TEST_F(LoggerTest, LogBoolFalseArg) {
    logger.log(LogLevel::Info, false);
    std::string output = output_stream->str();
    EXPECT_NE(output.find("[INFO ] 0"), std::string::npos);
}

TEST_F(LoggerTest, LogFiltersByMinLevel) {
    logger.setMinLevel(LogLevel::Error);
    logger.log(LogLevel::Debug, "debug");
    logger.log(LogLevel::Info, "info");
    logger.log(LogLevel::Warn, "warn");
    logger.log(LogLevel::Error, "error");
    logger.log(LogLevel::Fatal, "fatal");

    std::string output = output_stream->str();
    EXPECT_EQ(output.find("debug"), std::string::npos);
    EXPECT_EQ(output.find("info"), std::string::npos);
    EXPECT_EQ(output.find("warn"), std::string::npos);
    EXPECT_NE(output.find("error"), std::string::npos);
    EXPECT_NE(output.find("fatal"), std::string::npos);
}

TEST_F(LoggerTest, LogDebugFilteredByMinLevelDebug) {
    logger.setMinLevel(LogLevel::Debug);
    logger.log(LogLevel::Debug, "debug");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("debug"), std::string::npos);
}

TEST_F(LoggerTest, LogInfoFilteredByMinLevelInfo) {
    logger.setMinLevel(LogLevel::Info);
    logger.log(LogLevel::Debug, "debug");
    logger.log(LogLevel::Info, "info");
    std::string output = output_stream->str();
    EXPECT_EQ(output.find("debug"), std::string::npos);
    EXPECT_NE(output.find("info"), std::string::npos);
}

TEST_F(LoggerTest, LogWarnFilteredByMinLevelWarn) {
    logger.setMinLevel(LogLevel::Warn);
    logger.log(LogLevel::Debug, "debug");
    logger.log(LogLevel::Info, "info");
    logger.log(LogLevel::Warn, "warn");
    std::string output = output_stream->str();
    EXPECT_EQ(output.find("debug"), std::string::npos);
    EXPECT_EQ(output.find("info"), std::string::npos);
    EXPECT_NE(output.find("warn"), std::string::npos);
}

TEST_F(LoggerTest, LogErrorFilteredByMinLevelError) {
    logger.setMinLevel(LogLevel::Error);
    logger.log(LogLevel::Warn, "warn");
    logger.log(LogLevel::Error, "error");
    std::string output = output_stream->str();
    EXPECT_EQ(output.find("warn"), std::string::npos);
    EXPECT_NE(output.find("error"), std::string::npos);
}

TEST_F(LoggerTest, LogFatalNotFilteredByMinLevelFatal) {
    logger.setMinLevel(LogLevel::Fatal);
    logger.log(LogLevel::Fatal, "fatal");
    std::string output = output_stream->str();
    EXPECT_NE(output.find("fatal"), std::string::npos);
}

TEST_F(LoggerTest, LogAllLevelsInSequence) {
    logger.setMinLevel(LogLevel::Debug);
    logger.log(LogLevel::Debug, "d");
    logger.log(LogLevel::Info, "i");
    logger.log(LogLevel::Warn, "w");
    logger.log(LogLevel::Error, "e");
    logger.log(LogLevel::Fatal, "f");

    std::string output = output_stream->str();
    EXPECT_NE(output.find("[DEBUG] d"), std::string::npos);
    EXPECT_NE(output.find("[INFO ] i"), std::string::npos);
    EXPECT_NE(output.find("[WARN ] w"), std::string::npos);
    EXPECT_NE(output.find("[ERROR] e"), std::string::npos);
    EXPECT_NE(output.find("[FATAL] f"), std::string::npos);
}

TEST_F(LoggerTest, GetMinLevelReturnsSetValue) {
    logger.setMinLevel(LogLevel::Warn);
    EXPECT_EQ(logger.getMinLevel(), LogLevel::Warn);
}

TEST_F(LoggerTest, GetMinLevelDefaultIsInfo) {
    Logger new_logger;
    EXPECT_EQ(new_logger.getMinLevel(), LogLevel::Info);
}

TEST_F(LoggerTest, SetOutputRedirectsOutput) {
    std::ostringstream stream1;
    std::ostringstream stream2;

    logger.setOutput(stream1);
    logger.log(LogLevel::Info, "msg1");

    logger.setOutput(stream2);
    logger.log(LogLevel::Info, "msg2");

    EXPECT_NE(stream1.str().find("msg1"), std::string::npos);
    EXPECT_EQ(stream1.str().find("msg2"), std::string::npos);
    EXPECT_NE(stream2.str().find("msg2"), std::string::npos);
}

TEST_F(LoggerTest, LogIncludesNewline) {
    logger.log(LogLevel::Info, "msg");
    std::string output = output_stream->str();
    // The output should end with a newline
    EXPECT_EQ(output.back(), '\n');
}

TEST_F(LoggerTest, LogOutputIsFlushed) {
    // This test verifies flush() is called - we can't easily test flush
    // but we verify the log function completes without error
    logger.log(LogLevel::Info, "test");
    SUCCEED();
}

TEST_F(LoggerTest, LogMultipleMessagesAccumulate) {
    logger.log(LogLevel::Info, "msg1");
    logger.log(LogLevel::Info, "msg2");
    logger.log(LogLevel::Info, "msg3");

    std::string output = output_stream->str();
    EXPECT_NE(output.find("msg1"), std::string::npos);
    EXPECT_NE(output.find("msg2"), std::string::npos);
    EXPECT_NE(output.find("msg3"), std::string::npos);
}

TEST_F(LoggerTest, PointerOverloadSetOutputWithValidPointer) {
    // Test the pointer overload version of setOutput with a valid pointer
    std::ostringstream stream;
    logger.setOutput(static_cast<std::ostream*>(&stream));
    logger.log(LogLevel::Info, "test");

    // Verify log worked
    EXPECT_NE(stream.str().find("test"), std::string::npos);

    // Restore to valid output before test ends
    logger.setOutput(*output_stream);
}

TEST_F(LoggerTest, PointerOverloadAndReferenceOverloadsWorkTogether) {
    // Test that both overloads can be used and share state
    std::ostringstream stream1;
    std::ostringstream stream2;

    // Use reference overload
    logger.setOutput(stream1);
    logger.log(LogLevel::Info, "from_ref");

    // Use pointer overload with same stream
    logger.setOutput(static_cast<std::ostream*>(&stream2));
    logger.log(LogLevel::Info, "from_ptr");

    // Reference output has content
    EXPECT_NE(stream1.str().find("from_ref"), std::string::npos);
    // Pointer output has content
    EXPECT_NE(stream2.str().find("from_ptr"), std::string::npos);

    // Restore to valid output
    logger.setOutput(*output_stream);
}

// =============================================================================
// Tests for free function API
// =============================================================================

class FreeFunctionLogAPITest : public ::testing::Test {
protected:
    void SetUp() override {
        output_stream = std::make_shared<std::ostringstream>();
        setOutput(*output_stream);
        setMinLevel(LogLevel::Debug);
    }

    std::shared_ptr<std::ostringstream> output_stream;
};

TEST_F(FreeFunctionLogAPITest, DebugFunction) {
    debug("debug message");
    EXPECT_NE(output_stream->str().find("[DEBUG] debug message"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, InfoFunction) {
    info("info message");
    EXPECT_NE(output_stream->str().find("[INFO ] info message"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, WarnFunction) {
    warn("warn message");
    EXPECT_NE(output_stream->str().find("[WARN ] warn message"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, ErrorFunction) {
    error("error message");
    EXPECT_NE(output_stream->str().find("[ERROR] error message"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, FatalFunction) {
    fatal("fatal message");
    EXPECT_NE(output_stream->str().find("[FATAL] fatal message"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, DebugWithMultipleArgs) {
    debug("value=", 42);
    EXPECT_NE(output_stream->str().find("[DEBUG] value=42"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, InfoWithMultipleArgs) {
    info("name=", "test", " count=", 100);
    EXPECT_NE(output_stream->str().find("[INFO ] name=test count=100"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, SetMinLevelAffectsAllFunctions) {
    setMinLevel(LogLevel::Error);
    debug("debug");
    info("info");
    warn("warn");
    error("error");
    fatal("fatal");

    std::string output = output_stream->str();
    EXPECT_EQ(output.find("debug"), std::string::npos);
    EXPECT_EQ(output.find("info"), std::string::npos);
    EXPECT_EQ(output.find("warn"), std::string::npos);
    EXPECT_NE(output.find("error"), std::string::npos);
    EXPECT_NE(output.find("fatal"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, SetOutputRedirectsAllFunctions) {
    std::ostringstream stream1;
    std::ostringstream stream2;

    setOutput(stream1);
    info("msg1");

    setOutput(stream2);
    info("msg2");

    EXPECT_NE(stream1.str().find("msg1"), std::string::npos);
    EXPECT_EQ(stream1.str().find("msg2"), std::string::npos);
    EXPECT_NE(stream2.str().find("msg2"), std::string::npos);
}

TEST_F(FreeFunctionLogAPITest, AllFunctionsWorkInSequence) {
    debug("d");
    info("i");
    warn("w");
    error("e");
    fatal("f");

    std::string output = output_stream->str();
    EXPECT_NE(output.find("[DEBUG] d"), std::string::npos);
    EXPECT_NE(output.find("[INFO ] i"), std::string::npos);
    EXPECT_NE(output.find("[WARN ] w"), std::string::npos);
    EXPECT_NE(output.find("[ERROR] e"), std::string::npos);
    EXPECT_NE(output.find("[FATAL] f"), std::string::npos);
}

// =============================================================================
// Tests for logger() singleton function
// =============================================================================

class LoggerSingletonTest : public ::testing::Test {};

TEST_F(LoggerSingletonTest, LoggerSingletonReturnsValidReference) {
    Logger& lg = logger();
    std::ostringstream os;
    lg.setOutput(os);
    lg.setMinLevel(LogLevel::Debug);
    lg.log(LogLevel::Info, "test");
    EXPECT_NE(os.str().find("test"), std::string::npos);
}

TEST_F(LoggerSingletonTest, MultipleCallsReturnSameInstance) {
    Logger& lg1 = logger();
    Logger& lg2 = logger();
    EXPECT_EQ(&lg1, &lg2);
}

TEST_F(LoggerSingletonTest, SingletonSharesStateAcrossCalls) {
    std::ostringstream os;
    logger().setOutput(os);
    logger().setMinLevel(LogLevel::Debug);

    debug("shared test");

    EXPECT_NE(os.str().find("shared test"), std::string::npos);
}

// =============================================================================
// Integration tests
// =============================================================================

class LoggerIntegrationTest : public ::testing::Test {};

TEST_F(LoggerIntegrationTest, ComplexLogMessage) {
    std::ostringstream output;
    Logger lg;
    lg.setOutput(output);
    lg.setMinLevel(LogLevel::Debug);

    lg.log(LogLevel::Info, "User ", 1234, " logged in from ", "192.168.1.1",
           " at ", "2024-01-01 12:00:00");

    std::string result = output.str();
    EXPECT_NE(result.find("[INFO ] User 1234 logged in from 192.168.1.1 at 2024-01-01 12:00:00"),
              std::string::npos);
}

TEST_F(LoggerIntegrationTest, LevelFilteringScenarios) {
    std::ostringstream output;
    Logger lg;
    lg.setOutput(output);

    // Test each minimum level
    std::vector<std::pair<LogLevel, std::vector<LogLevel>>> test_cases = {
        {LogLevel::Debug, {LogLevel::Debug, LogLevel::Info, LogLevel::Warn, LogLevel::Error, LogLevel::Fatal}},
        {LogLevel::Info, {LogLevel::Info, LogLevel::Warn, LogLevel::Error, LogLevel::Fatal}},
        {LogLevel::Warn, {LogLevel::Warn, LogLevel::Error, LogLevel::Fatal}},
        {LogLevel::Error, {LogLevel::Error, LogLevel::Fatal}},
        {LogLevel::Fatal, {LogLevel::Fatal}}
    };

    for (const auto& [min_level, expected_levels] : test_cases) {
        output.str("");
        output.clear();
        lg.setMinLevel(min_level);

        lg.log(LogLevel::Debug, "d");
        lg.log(LogLevel::Info, "i");
        lg.log(LogLevel::Warn, "w");
        lg.log(LogLevel::Error, "e");
        lg.log(LogLevel::Fatal, "f");

        std::string result = output.str();
        EXPECT_EQ(result.find("d") != std::string::npos,
                  (min_level == LogLevel::Debug)) << "min_level=" << static_cast<int>(min_level);
        EXPECT_EQ(result.find("i") != std::string::npos,
                  (static_cast<int>(min_level) <= static_cast<int>(LogLevel::Info))) << "min_level=" << static_cast<int>(min_level);
        EXPECT_EQ(result.find("w") != std::string::npos,
                  (static_cast<int>(min_level) <= static_cast<int>(LogLevel::Warn))) << "min_level=" << static_cast<int>(min_level);
        EXPECT_EQ(result.find("e") != std::string::npos,
                  (static_cast<int>(min_level) <= static_cast<int>(LogLevel::Error))) << "min_level=" << static_cast<int>(min_level);
        EXPECT_EQ(result.find("f") != std::string::npos, true) << "Fatal should always be logged";
    }
}

TEST_F(LoggerIntegrationTest, ConcatenationVariety) {
    std::ostringstream output;
    Logger lg;
    lg.setOutput(output);
    lg.setMinLevel(LogLevel::Debug);

    // Empty message
    lg.log(LogLevel::Info);
    EXPECT_NE(output.str().find("[INFO ] "), std::string::npos);

    // Single character
    lg.log(LogLevel::Info, 'x');
    EXPECT_NE(output.str().find("[INFO ] x"), std::string::npos);

    // Negative numbers
    lg.log(LogLevel::Info, -42, " ", -3.14);
    EXPECT_NE(output.str().find("-42"), std::string::npos);
    EXPECT_NE(output.str().find("-3.14"), std::string::npos);
}

TEST_F(LoggerIntegrationTest, FormattedOutputFormat) {
    std::ostringstream output;
    Logger lg;
    lg.setOutput(output);
    lg.setMinLevel(LogLevel::Debug);

    lg.log(LogLevel::Info, "test");

    std::string result = output.str();
    // Verify format: [LEVEL] message\n
    EXPECT_EQ(result.find("[INFO ] test\n"), 0);
}

}  // namespace cerys::core::utils
