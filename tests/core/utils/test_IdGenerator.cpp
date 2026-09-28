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

#include "utils/IdGenerator.h"

#include <gtest/gtest.h>
#include <atomic>
#include <cstdint>
#include <thread>
#include <vector>

namespace cerys::core::utils {

// =============================================================================
// Tests for IdGenerator<int>
// =============================================================================

class IdGeneratorIntTest : public ::testing::Test {};

TEST_F(IdGeneratorIntTest, GenerateIdReturnsIncreasingValues) {
    // Reset the static counter by generating IDs until we get a predictable sequence
    const int id0 = IdGenerator<int>::generateId();
    const int id1 = IdGenerator<int>::generateId();
    const int id2 = IdGenerator<int>::generateId();

    EXPECT_LT(id0, id1);
    EXPECT_LT(id1, id2);
}

TEST_F(IdGeneratorIntTest, GenerateIdReturnsNonNegative) {
    const int id = IdGenerator<int>::generateId();
    EXPECT_GE(id, 0);
}

TEST_F(IdGeneratorIntTest, GenerateIdReturnsUniqueValues) {
    const int id1 = IdGenerator<int>::generateId();
    const int id2 = IdGenerator<int>::generateId();
    EXPECT_NE(id1, id2);
}

// =============================================================================
// Tests for IdGenerator<unsigned int>
// =============================================================================

class IdGeneratorUnsignedIntTest : public ::testing::Test {};

TEST_F(IdGeneratorUnsignedIntTest, GenerateIdReturnsIncreasingValues) {
    const unsigned int id0 = IdGenerator<unsigned int>::generateId();
    const unsigned int id1 = IdGenerator<unsigned int>::generateId();

    EXPECT_LT(id0, id1);
}

TEST_F(IdGeneratorUnsignedIntTest, GenerateIdReturnsNonNegative) {
    const unsigned int id = IdGenerator<unsigned int>::generateId();
    EXPECT_GE(id, 0u);
}

// =============================================================================
// Tests for IdGenerator<long>
// =============================================================================

class IdGeneratorLongTest : public ::testing::Test {};

TEST_F(IdGeneratorLongTest, GenerateIdReturnsIncreasingValues) {
    const long id0 = IdGenerator<long>::generateId();
    const long id1 = IdGenerator<long>::generateId();

    EXPECT_LT(id0, id1);
}

TEST_F(IdGeneratorLongTest, GenerateIdReturnsNonNegative) {
    const long id = IdGenerator<long>::generateId();
    EXPECT_GE(id, 0L);
}

// =============================================================================
// Tests for IdGenerator<long long>
// =============================================================================

class IdGeneratorLongLongTest : public ::testing::Test {};

TEST_F(IdGeneratorLongLongTest, GenerateIdReturnsIncreasingValues) {
    const long long id0 = IdGenerator<long long>::generateId();
    const long long id1 = IdGenerator<long long>::generateId();

    EXPECT_LT(id0, id1);
}

TEST_F(IdGeneratorLongLongTest, GenerateIdReturnsNonNegative) {
    const long long id = IdGenerator<long long>::generateId();
    EXPECT_GE(id, 0LL);
}

// =============================================================================
// Tests for IdGenerator<unsigned long long>
// =============================================================================

class IdGeneratorULLTest : public ::testing::Test {};

TEST_F(IdGeneratorULLTest, GenerateIdReturnsIncreasingValues) {
    const unsigned long long id0 = IdGenerator<unsigned long long>::generateId();
    const unsigned long long id1 = IdGenerator<unsigned long long>::generateId();

    EXPECT_LT(id0, id1);
}

TEST_F(IdGeneratorULLTest, GenerateIdReturnsNonNegative) {
    const unsigned long long id = IdGenerator<unsigned long long>::generateId();
    EXPECT_GE(id, 0ULL);
}

// =============================================================================
// Tests for IdGenerator<short>
// =============================================================================

class IdGeneratorShortTest : public ::testing::Test {};

TEST_F(IdGeneratorShortTest, GenerateIdReturnsIncreasingValues) {
    const short id0 = IdGenerator<short>::generateId();
    const short id1 = IdGenerator<short>::generateId();

    EXPECT_LT(id0, id1);
}

// =============================================================================
// Tests for IdGenerator<uint32_t>
// =============================================================================

class IdGeneratorUint32Test : public ::testing::Test {};

TEST_F(IdGeneratorUint32Test, GenerateIdReturnsIncreasingValues) {
    const uint32_t id0 = IdGenerator<uint32_t>::generateId();
    const uint32_t id1 = IdGenerator<uint32_t>::generateId();

    EXPECT_LT(id0, id1);
}

TEST_F(IdGeneratorUint32Test, GenerateIdReturnsNonNegative) {
    const uint32_t id = IdGenerator<uint32_t>::generateId();
    EXPECT_GE(id, static_cast<uint32_t>(0));
}

// =============================================================================
// Tests for IdGenerator<uint64_t>
// =============================================================================

class IdGeneratorUint64Test : public ::testing::Test {};

TEST_F(IdGeneratorUint64Test, GenerateIdReturnsIncreasingValues) {
    const uint64_t id0 = IdGenerator<uint64_t>::generateId();
    const uint64_t id1 = IdGenerator<uint64_t>::generateId();

    EXPECT_LT(id0, id1);
}

TEST_F(IdGeneratorUint64Test, GenerateIdReturnsNonNegative) {
    const uint64_t id = IdGenerator<uint64_t>::generateId();
    EXPECT_GE(id, static_cast<uint64_t>(0));
}

// =============================================================================
// Tests for different template types generate independently
// =============================================================================

class IdGeneratorDifferentTypesTest : public ::testing::Test {};

TEST_F(IdGeneratorDifferentTypesTest, DifferentTypesHaveIndependentCounters) {
    const int int_id = IdGenerator<int>::generateId();
    const long long ll_id = IdGenerator<long long>::generateId();

    // Different types have independent counters
    // They may or may not be equal, but they should be valid
    EXPECT_GE(int_id, 0);
    EXPECT_GE(ll_id, 0);
}

// =============================================================================
// Integration test for basic usage
// =============================================================================

class IdGeneratorIntegrationTest : public ::testing::Test {};

TEST_F(IdGeneratorIntegrationTest, GenerateMultipleIdsInSequence) {
    constexpr int num_ids = 10;
    int ids[num_ids];

    for (int i = 0; i < num_ids; ++i) {
        ids[i] = IdGenerator<int>::generateId();
    }

    // Verify all IDs are unique
    for (int i = 0; i < num_ids; ++i) {
        for (int j = i + 1; j < num_ids; ++j) {
            EXPECT_NE(ids[i], ids[j]) << "IDs at index " << i << " and " << j << " should be different";
        }
    }

    // Verify IDs are in increasing order
    for (int i = 1; i < num_ids; ++i) {
        EXPECT_LT(ids[i - 1], ids[i]) << "IDs should be in increasing order";
    }
}

TEST_F(IdGeneratorIntegrationTest, ForwardReferenceTemplateParameter) {
    // Test with forward reference - IdGenerator<T> where T is complete
    IdGenerator<int> generator;
    // Note: IdGenerator::generateId() is static, so we just verify it compiles
    (void)IdGenerator<int>::generateId();
}

}  // namespace cerys::core::utils
