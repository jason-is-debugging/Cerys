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

#include "base/OperatorRegistry.h"
#include "ml/Variable.h"

namespace cerys::core::ml {
Variable::Variable(const math::TensorData& tensorData) {
    this->mTensorData = tensorData;
    this->mParentVariables.clear();
    this->mOperatorID = base::NullOperatorID;
}

void Variable::runOp(std::vector<Variable> vars, const OperatorID operatorID) {
    std::vector<math::TensorData> tensorDatas(vars.size() + 1);
    for (SizeT i = 0; i < vars.size(); i++) {
        tensorDatas[i] = vars[i].mTensorData;
    }
    math::TensorData::runOp(tensorDatas, operatorID);
    Variable result(tensorDatas[tensorDatas.size() - 1]);
    result.mParentVariables.clear();
    result.mOperatorID = operatorID;
    result.mParentVariables.insert(result.mParentVariables.begin(),
                                   tensorDatas.begin(),
                                   tensorDatas.end());
    vars[vars.size() - 1] = result;
}

}