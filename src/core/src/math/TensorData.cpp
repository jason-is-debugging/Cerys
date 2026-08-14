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

#include <format>
#include <stdexcept>

#include "base/OperatorRegistry.h"
#include "compute/Dispatcher.h"

namespace cerys::core::math {
TensorData::TensorData() : mShape(TensorShape()),
                           mStride(TensorStride()),
                           mStorage(nullptr),
                           mMetadata(TensorMetadata()),
                           mOffset(0) {
}

TensorData::~TensorData() = default;

ScalarData TensorData::at(std::vector<SizeT> indices) {
}

ScalarData TensorData::at(std::vector<SizeT> index) const {
}

TensorData TensorData::operator[](SizeT index) {
}

TensorData TensorData::operator[](SizeT index) const {
}

void TensorData::reshape(TensorShape newShape) {
}

void TensorData::permute(TensorShape newShape) {
}

void TensorData::fill(ScalarData data) {
}

TensorShape TensorData::shape() const {
    return mShape;
}

TensorStride TensorData::stride() const {
    return mStride;
}


TensorMetadata TensorData::metadata() const {
    return mMetadata;
}

SizeT TensorData::offset() const {
    return mOffset;
}

base::StoragePtr TensorData::storage() {
    return mStorage;
}

TensorShape& TensorData::shapeRef() {
    return mShape;
}

TensorStride& TensorData::strideRef() {
    return mStride;
}

TensorMetadata& TensorData::metadataRef() {
    return mMetadata;
}

SizeT& TensorData::offsetRef() {
    return mOffset;
}

SizeT TensorData::numel() const {
    return mShape.getTotalElem();
}

SizeT TensorData::ndims() const {
    return mShape.ndims();
}

bool TensorData::isContiguous() const {
    return mMetadata.mIsContiguous;
}

DeviceID TensorData::deviceID() const {
    return mMetadata.mDeviceID;
}


DataTypeID reduceDataType();

void TensorData::runOp(
    const std::vector<TensorData>& tensorDatas,
    const OperatorID operatorID) {

    if (tensorDatas.empty()) {
        throw std::runtime_error(std::format(
            "The operands are empty while run Operator {}",
            base::getOperatorName(operatorID)
            ));
    }
    DeviceID deviceID = tensorDatas.front().deviceID();
    DataTypeID dataTypeId = reduceDataType();
    const compute::ComputeContext ctx(tensorDatas.front().deviceID(), operatorID);
    compute::Dispatcher::instance().dispatch(ctx,
                                             {operatorID, deviceID, dataTypeId},
                                             tensorDatas);
}


}