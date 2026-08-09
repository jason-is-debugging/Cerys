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


#include "math/TensorData.h"

#include "compute/Dispatcher.h"

namespace cerys::core::math {
TensorData::TensorData() : mShape(TensorShape()),
                           mStride(TensorStride()),
                           mStorage(nullptr),
                           mMetadata(TensorMetadata()),
                           mOffset(0) {
}

TensorData::~TensorData() = default;

TensorData TensorData::runOp(
    std::vector<TensorData> tensorDatas,
    OperatorID operatorID) {
    TensorData result;

    compute::Dispatcher::instance();

    return result;
}
}