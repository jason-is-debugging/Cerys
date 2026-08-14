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

#ifndef CERYS_DISPATCHERKEY_D4D3B7F1A50C486DAC79FFEF8F36B302_H
#define CERYS_DISPATCHERKEY_D4D3B7F1A50C486DAC79FFEF8F36B302_H

#include <cstddef>
#include <format>
#include <functional>
#include <string>

#include "defines.h"

namespace cerys::core::compute {
class DispatcherKey {
public:
    DispatcherKey(
        const OperatorID operatorID,
        const DeviceID deviceID,
        const DataTypeID dataTypeID
        ) : mOperatorID(operatorID),
            mDeviceID(deviceID),
            mDataTypeID(dataTypeID) {
    }

    [[nodiscard]] std::string toString() const {
        return std::vformat("DispatcherKey{{OperatorID: {}}, DeviceID: {}, DataTypeID: {}}",
                            std::make_format_args(this->mOperatorID,
                                                  this->mDeviceID,
                                                  this->mDataTypeID));
    }

    [[nodiscard]] OperatorID getOperatorID() const {
        return mOperatorID;
    }

    [[nodiscard]] DeviceID getDeviceID() const {
        return mDeviceID;
    }

    [[nodiscard]] DataTypeID getDataTypeID() const {
        return mDataTypeID;
    }

    void setOperatorID(const OperatorID operatorID) {
        mOperatorID = operatorID;
    }

    void setDeviceID(const DeviceID deviceID) {
        mDeviceID = deviceID;
    }

    void setDataTypeID(const DataTypeID dataTypeID) {
        mDataTypeID = dataTypeID;
    }

private:
    OperatorID mOperatorID;
    DeviceID mDeviceID;
    DataTypeID mDataTypeID;
};

inline bool operator==(const DispatcherKey& lhs, const DispatcherKey& rhs) noexcept {
    return lhs.getOperatorID() == rhs.getOperatorID()
        && lhs.getDeviceID()   == rhs.getDeviceID()
        && lhs.getDataTypeID() == rhs.getDataTypeID();
}
}

template<>
struct std::hash<cerys::core::compute::DispatcherKey> {
    std::size_t operator()(const cerys::core::compute::DispatcherKey& key) const noexcept {
        auto h = static_cast<std::size_t>(key.getOperatorID());
        h = h * 0x9E3779B97F4A7C15ULL ^ static_cast<std::size_t>(key.getDeviceID());
        h = h * 0x9E3779B97F4A7C15ULL ^ static_cast<std::size_t>(key.getDataTypeID());
        return h;
    }
};

#endif //CERYS_DISPATCHERKEY_D4D3B7F1A50C486DAC79FFEF8F36B302_H