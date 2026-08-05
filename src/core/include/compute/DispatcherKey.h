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

    OperatorID getOperatorID() const {
        return mOperatorID;
    }

    DeviceID getDeviceID() const {
        return mDeviceID;
    }

    DataTypeID getDataTypeID() const {
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
}

#endif //CERYS_DISPATCHERKEY_D4D3B7F1A50C486DAC79FFEF8F36B302_H