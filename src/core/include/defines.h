//  Copyright (c) 2025-2026 Contributors of Cerys(https://github.com/jason-is-debugging/Cerys)
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

#ifndef INC_868742493465492C921FD4EACABFA677
#define INC_868742493465492C921FD4EACABFA677
#include <cmath>
#include <cstdint>
#include <string_view>

namespace cerys::core {
using Int32 = std::int32_t;
using UInt32 = std::uint32_t;
using Int64 = std::int64_t;
using UInt64 = std::uint64_t;
using Float = std::float_t;
using Double = std::double_t;
using Int8 = std::int8_t;
using UInt8 = std::uint8_t;
using Int16 = std::int16_t;
using UInt16 = std::uint16_t;

using DataTypeID = Int32;
using OperatorID = Int32;
using DeviceID = Int32;

using SizeT = Int64;

// this pointer should have same attributes with char *
using Pointer = char*;

}

#endif //INC_868742493465492C921FD4EACABFA677