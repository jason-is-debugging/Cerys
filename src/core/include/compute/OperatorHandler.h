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
#ifndef CERYS_OPERATORHANDLER_281F81D8B789401E856D2B8581DC3293_H
#define CERYS_OPERATORHANDLER_281F81D8B789401E856D2B8581DC3293_H

#include <functional>
#include <vector>

#include "defines.h"
#include "compute/ComputeContext.h"

namespace cerys::core::compute {


// One operator implementation is a callable that, given a compute context
// and a flat list of input/output tensors, performs the work on the device
// the context describes. The signature is intentionally broad so that the
// same type can be used for CPU kernels, GPU kernels, autograd backward
// passes, and the future Python-bound reference implementations.
//
// Return value is reserved for future use (e.g. status / async handle).
// Today it must simply be a pointer to the output TensorData (the last
// element of `tensors`), or nullptr if the handler has no outputs.
using OperatorHandler = std::function<void*(
    ComputeContext& /*ctx*/,
    std::vector<TensorData>& /*tensors*/
    )>;

} // namespace cerys::core::math

#endif  // CERYS_OPERATORHANDLER_281F81D8B789401E856D2B8581DC3293_H