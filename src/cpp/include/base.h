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
#ifndef CERYS_DEFINES_18E31C05AF0141C19A2F6CECFAE14231_H
#define CERYS_DEFINES_18E31C05AF0141C19A2F6CECFAE14231_H

#include "core/include/defines.h"

namespace cerys {
using Int32 = core::Int32;
using UInt32 = core::UInt32;
using Int64 = core::Int64;
using UInt64 = core::UInt64;
using Float = core::Float;
using Double = core::Double;
using Int8 = core::Int8;
using UInt8 = core::UInt8;
using Int16 = core::Int16;
using UInt16 = core::UInt16;

using DataTypeID = Int32;
using OperatorID = Int32;
using DeviceID = Int32;

using SizeT = Int64;

// this pointer should have same attributes with char *
using Pointer = char*;

}


#endif //CERYS_DEFINES_18E31C05AF0141C19A2F6CECFAE14231_H
