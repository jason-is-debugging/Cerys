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

#include "compute/Dispatcher.h"
#include "math/TensorData.h"

namespace cerys::core::compute {
void Dispatcher::dispatch(ComputeContext ctx, DispatcherKey key,
    const std::vector<math::TensorData>& vector) {
    auto handler = mDispatchMap.find(key);
    if (handler == mDispatchMap.end()) {
        throw std::invalid_argument(std::format("Unknown dispatch key: {}", key));

    }
}

Dispatcher::Dispatcher() {
}
}

