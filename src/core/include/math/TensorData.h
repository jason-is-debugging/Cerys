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

#ifndef CERYS_TENSORDATA_5117AA3BF8A04C25864C1CE97F4866A5_H
#define CERYS_TENSORDATA_5117AA3BF8A04C25864C1CE97F4866A5_H
#include "ScalarData.h"
#include "TensorMetadata.h"
#include "TensorShape.h"
#include "TensorStride.h"
#include "base/Storage.h"

namespace cerys::core::math {
class TensorData {
public:
    TensorData();
    ~TensorData();

    ScalarData at(std::vector<SizeT> indices);
    const ScalarData at(std::vector<SizeT> index) const;
    TensorData operator[](SizeT index);
    const TensorData operator[](SizeT index) const;

    void reshape(TensorShape newShape);
    void permute(TensorShape newShape);
    void fill(ScalarData data);

    TensorData sum();
    TensorData mean();
    TensorData min();
    TensorData max();

    TensorShape shape();
    TensorStride stride();
    TensorMetadata metadata();
    SizeT offset();
    base::StoragePtr storage();

    SizeT numel();
    SizeT ndims();
    bool isContigugus();

    // a common method to run all operators, replace methods like `add` `sub`
    static TensorData runOp(std::vector<TensorData> tensorDatas, OperatorID operatorID);

private:
    TensorShape mShape;
    TensorStride mStride;
    base::StoragePtr mStorage;
    TensorMetadata mMetadata;
    SizeT mOffset;
};
}

#endif //CERYS_TENSORDATA_5117AA3BF8A04C25864C1CE97F4866A5_H
