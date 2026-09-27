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

#include "utils/exception.h"

#include <gtest/gtest.h>

#include <sstream>
#include <stdexcept>
#include <string>

namespace cerys::core::utils {

// =============================================================================
// Tests for detail::concatToString - internal helper
// =============================================================================

class ConcatToStringTest : public ::testing::Test {};

TEST_F(ConcatToStringTest, EmptyArgsReturnsEmptyString) {
    std::string result = detail::concatToString();
    EXPECT_EQ(result, "");
}

TEST_F(ConcatToStringTest, SingleStringArg) {
    std::string result = detail::concatToString(std::string("hello"));
    EXPECT_EQ(result, "hello");
}

TEST_F(ConcatToStringTest, SingleIntArg) {
    std::string result = detail::concatToString(42);
    EXPECT_EQ(result, "42");
}

TEST_F(ConcatToStringTest, MultipleArgsIntAndString) {
    std::string result = detail::concatToString("value=", 123);
    EXPECT_EQ(result, "value=123");
}

TEST_F(ConcatToStringTest, MultipleArgsStringIntString) {
    std::string result = detail::concatToString("a", 1, "b", 2);
    EXPECT_EQ(result, "a1b2");
}

TEST_F(ConcatToStringTest, DoubleArg) {
    std::string result = detail::concatToString(3.14159);
    EXPECT_EQ(result, "3.14159");
}

TEST_F(ConcatToStringTest, MultipleDoubleArgs) {
    std::string result = detail::concatToString(1.5, " + ", 2.5, " = ", 4.0);
    EXPECT_EQ(result, "1.5 + 2.5 = 4");
}

TEST_F(ConcatToStringTest, CharPointerArg) {
    std::string result = detail::concatToString("test");
    EXPECT_EQ(result, "test");
}

TEST_F(ConcatToStringTest, MultipleCharPointerArgs) {
    std::string result = detail::concatToString("one", " two", " three");
    EXPECT_EQ(result, "one two three");
}

TEST_F(ConcatToStringTest, BoolTrueArg) {
    std::string result = detail::concatToString(true);
    EXPECT_EQ(result, "1");
}

TEST_F(ConcatToStringTest, BoolFalseArg) {
    std::string result = detail::concatToString(false);
    EXPECT_EQ(result, "0");
}

TEST_F(ConcatToStringTest, MixedTypesIntDoubleString) {
    std::string result = detail::concatToString("id:", 1, " value:", 99.5, " name:", "test");
    EXPECT_EQ(result, "id:1 value:99.5 name:test");
}

TEST_F(ConcatToStringTest, SingleCharArg) {
    std::string result = detail::concatToString('X');
    EXPECT_EQ(result, "X");
}

TEST_F(ConcatToStringTest, UnsignedIntArg) {
    std::string result = detail::concatToString(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(ConcatToStringTest, NegativeIntArg) {
    std::string result = detail::concatToString(-100);
    EXPECT_EQ(result, "-100");
}

// =============================================================================
// Tests for detail::appendToStream
// =============================================================================

class AppendToStreamTest : public ::testing::Test {};

TEST_F(AppendToStreamTest, AppendInt) {
    std::ostringstream os;
    detail::appendToStream(os, 42);
    EXPECT_EQ(os.str(), "42");
}

TEST_F(AppendToStreamTest, AppendString) {
    std::ostringstream os;
    detail::appendToStream(os, std::string("hello"));
    EXPECT_EQ(os.str(), "hello");
}

TEST_F(AppendToStreamTest, AppendDouble) {
    std::ostringstream os;
    detail::appendToStream(os, 2.718);
    EXPECT_EQ(os.str(), "2.718");
}

TEST_F(AppendToStreamTest, AppendRvalueReference) {
    std::ostringstream os;
    detail::appendToStream(os, std::string("move"));
    EXPECT_EQ(os.str(), "move");
}

TEST_F(AppendToStreamTest, AppendConstReference) {
    std::ostringstream os;
    const int val = 100;
    detail::appendToStream(os, val);
    EXPECT_EQ(os.str(), "100");
}

// =============================================================================
// Tests for detail::appendAllToStream - empty case (base case)
// =============================================================================

class AppendAllToStreamEmptyTest : public ::testing::Test {};

TEST_F(AppendAllToStreamEmptyTest, NoArgsLeavesStreamEmpty) {
    std::ostringstream os;
    detail::appendAllToStream(os);
    EXPECT_EQ(os.str(), "");
}

TEST_F(AppendAllToStreamEmptyTest, NoArgsPreservesExistingContent) {
    std::ostringstream os;
    os << "existing";
    detail::appendAllToStream(os);
    EXPECT_EQ(os.str(), "existing");
}

// =============================================================================
// Tests for detail::appendAllToStream - single arg
// =============================================================================

class AppendAllToStreamSingleArgTest : public ::testing::Test {};

TEST_F(AppendAllToStreamSingleArgTest, SingleInt) {
    std::ostringstream os;
    detail::appendAllToStream(os, 1);
    EXPECT_EQ(os.str(), "1");
}

TEST_F(AppendAllToStreamSingleArgTest, SingleString) {
    std::ostringstream os;
    detail::appendAllToStream(os, std::string("test"));
    EXPECT_EQ(os.str(), "test");
}

// =============================================================================
// Tests for detail::appendAllToStream - multiple args (recursive case)
// =============================================================================

class AppendAllToStreamMultiArgsTest : public ::testing::Test {};

TEST_F(AppendAllToStreamMultiArgsTest, TwoArgs) {
    std::ostringstream os;
    detail::appendAllToStream(os, "a", 1);
    EXPECT_EQ(os.str(), "a1");
}

TEST_F(AppendAllToStreamMultiArgsTest, ThreeArgs) {
    std::ostringstream os;
    detail::appendAllToStream(os, "x", 10, "y");
    EXPECT_EQ(os.str(), "x10y");
}

TEST_F(AppendAllToStreamMultiArgsTest, FourArgs) {
    std::ostringstream os;
    detail::appendAllToStream(os, "a", 1, "b", 2);
    EXPECT_EQ(os.str(), "a1b2");
}

TEST_F(AppendAllToStreamMultiArgsTest, FiveArgs) {
    std::ostringstream os;
    detail::appendAllToStream(os, "id=", 1, ", name=", "test", ", val=", 3.14);
    EXPECT_EQ(os.str(), "id=1, name=test, val=3.14");
}

// =============================================================================
// Tests for throwWithFmt - custom exception type
// =============================================================================

class ThrowWithFmtTest : public ::testing::Test {};

TEST_F(ThrowWithFmtTest, DefaultExceptionTypeIsRuntimeError) {
    try {
        throwWithFmt("custom error message");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "custom error message");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, CustomExceptionTypeInvalidArgument) {
    try {
        throwWithFmt<std::invalid_argument>("invalid: ", "value");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "invalid: value");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, CustomExceptionTypeOutOfRange) {
    try {
        throwWithFmt<std::out_of_range>("index ", 5, " out of range");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "index 5 out of range");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, CustomExceptionTypeLogicError) {
    try {
        throwWithFmt<std::logic_error>("logic error at step ", 3);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "logic error at step 3");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, CustomExceptionTypeRuntimeErrorExplicit) {
    try {
        throwWithFmt<std::runtime_error>("runtime error");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "runtime error");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, MixedTypesConcatenation) {
    try {
        throwWithFmt<std::runtime_error>("value=", 42, ", flag=", true);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "value=42, flag=1");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, DoubleConcatenation) {
    try {
        throwWithFmt<std::runtime_error>("pi=", 3.14159);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "pi=3.14159");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowWithFmtTest, EmptyString) {
    try {
        throwWithFmt<std::runtime_error>("");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

// =============================================================================
// Tests for throwRuntime
// =============================================================================

class ThrowRuntimeTest : public ::testing::Test {};

TEST_F(ThrowRuntimeTest, ThrowsRuntimeErrorWithString) {
    try {
        throwRuntime("runtime error occurred");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "runtime error occurred");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowRuntimeTest, ThrowsRuntimeErrorWithInt) {
    try {
        throwRuntime("error code: ", 404);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "error code: 404");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowRuntimeTest, ThrowsRuntimeErrorWithMultipleArgs) {
    try {
        throwRuntime("failed at step ", 2, " with code ", 500, ": ", "server error");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "failed at step 2 with code 500: server error");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowRuntimeTest, ThrowsRuntimeErrorWithDouble) {
    try {
        throwRuntime("value overflow: ", 1e10);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "value overflow: 1e+10");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowRuntimeTest, ThrowsRuntimeErrorWithBool) {
    try {
        throwRuntime("condition met: ", true);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "condition met: 1");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowRuntimeTest, ThrowsRuntimeErrorWithChar) {
    try {
        throwRuntime("char: ", 'Z');
        FAIL() << "Expected exception was not thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "char: Z");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

// =============================================================================
// Tests for throwInvalidArg
// =============================================================================

class ThrowInvalidArgTest : public ::testing::Test {};

TEST_F(ThrowInvalidArgTest, ThrowsInvalidArgumentWithString) {
    try {
        throwInvalidArg("invalid argument provided");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "invalid argument provided");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowInvalidArgTest, ThrowsInvalidArgumentWithInt) {
    try {
        throwInvalidArg("invalid index: ", -5);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "invalid index: -5");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowInvalidArgTest, ThrowsInvalidArgumentWithMultipleArgs) {
    try {
        throwInvalidArg("param '", "age", "' has invalid value: ", 999);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "param 'age' has invalid value: 999");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowInvalidArgTest, ThrowsInvalidArgumentWithDouble) {
    try {
        throwInvalidArg("negative value not allowed: ", -1.5);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "negative value not allowed: -1.5");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

// =============================================================================
// Tests for throwOutOfRange
// =============================================================================

class ThrowOutOfRangeTest : public ::testing::Test {};

TEST_F(ThrowOutOfRangeTest, ThrowsOutOfRangeWithString) {
    try {
        throwOutOfRange("index out of bounds");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "index out of bounds");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowOutOfRangeTest, ThrowsOutOfRangeWithInt) {
    try {
        throwOutOfRange("accessing index ", 100, " but size is ", 10);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "accessing index 100 but size is 10");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowOutOfRangeTest, ThrowsOutOfRangeWithMultipleArgs) {
    try {
        throwOutOfRange("vector[", 5, "] has max ", 3);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "vector[5] has max 3");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowOutOfRangeTest, ThrowsOutOfRangeWithZero) {
    try {
        throwOutOfRange("size is 0, cannot access position ", 0);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::out_of_range& e) {
        EXPECT_STREQ(e.what(), "size is 0, cannot access position 0");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

// =============================================================================
// Tests for throwLogic
// =============================================================================

class ThrowLogicTest : public ::testing::Test {};

TEST_F(ThrowLogicTest, ThrowsLogicErrorWithString) {
    try {
        throwLogic("precondition not met");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "precondition not met");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowLogicTest, ThrowsLogicErrorWithInt) {
    try {
        throwLogic("state error in step ", 4);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "state error in step 4");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowLogicTest, ThrowsLogicErrorWithMultipleArgs) {
    try {
        throwLogic("expected state ", 1, " but got ", 2, ": inconsistent");
        FAIL() << "Expected exception was not thrown";
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "expected state 1 but got 2: inconsistent");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

TEST_F(ThrowLogicTest, ThrowsLogicErrorWithDouble) {
    try {
        throwLogic("invalid calculation result: ", 0.0);
        FAIL() << "Expected exception was not thrown";
    } catch (const std::logic_error& e) {
        EXPECT_STREQ(e.what(), "invalid calculation result: 0");
    } catch (...) {
        FAIL() << "Wrong exception type thrown";
    }
}

// =============================================================================
// Integration tests combining multiple throw functions
// =============================================================================

class ExceptionIntegrationTest : public ::testing::Test {};

TEST_F(ExceptionIntegrationTest, AllThrowFunctionsPreserveMessageAccuracy) {
    // Test throwRuntime
    try {
        throwRuntime("message1");
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "message1");
    }

    // Test throwInvalidArg
    try {
        throwInvalidArg("message2");
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "message2");
    }

    // Test throwOutOfRange
    try {
        throwOutOfRange("message3");
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "message3");
    }

    // Test throwLogic
    try {
        throwLogic("message4");
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "message4");
    }

    // Test throwWithFmt with default type
    try {
        throwWithFmt("message5");
    } catch (const std::exception& e) {
        EXPECT_STREQ(e.what(), "message5");
    }
}

TEST_F(ExceptionIntegrationTest, TemplateInstantiationWithDifferentTypes) {
    // Test concatToString with various fundamental types
    EXPECT_EQ(detail::concatToString(char('A')), "A");
    EXPECT_EQ(detail::concatToString(short(10)), "10");
    EXPECT_EQ(detail::concatToString(long(1000000L)), "1000000");
    EXPECT_EQ(detail::concatToString(42ul), "42");
}

TEST_F(ExceptionIntegrationTest, ForwardReferencePreservation) {
    // Test that rvalue/lvalue semantics work correctly
    std::string s1 = "hello";
    std::string s2 = "world";
    std::string result = detail::concatToString(s1, " ", s2);
    EXPECT_EQ(result, "hello world");

    // Test with const reference
    const std::string cs = "const";
    std::string result2 = detail::concatToString(cs, " test");
    EXPECT_EQ(result2, "const test");
}

} // namespace cerys::core::utils
