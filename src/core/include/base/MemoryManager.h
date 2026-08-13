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
#ifndef CERYS_MEMORYMANAGER_080AB4275570491C9831938965AFCA24_H
#define CERYS_MEMORYMANAGER_080AB4275570491C9831938965AFCA24_H
#include <functional>

#include "defines.h"
#include "utils/exception.h"

namespace cerys::core::base {

using AllocateFun = std::function<void **(SizeT)>;
using DeallocateFun = std::function<void(void*, SizeT)>;

class MemoryManager {
public:
    static MemoryManager& instance() {
        static MemoryManager m;
        return m;
    }

    void registerAllocator(
        const DeviceID deviceID,
        const AllocateFun& allocFun
        ) {
        if (!mAllocator.contains(deviceID)) {
            mAllocator[deviceID].mAllocFun = allocFun;
        }
    }

    void registerDeallocator(
        const DeviceID deviceID,
        const DeallocateFun& deallocFun
        ) {
        if (!mAllocator.contains(deviceID)) {
            mAllocator[deviceID].mDeallocFun = deallocFun;
        }
    }

    void registerFullAllocator(
        const DeviceID deviceID,
        const AllocateFun& allocFun,
        const DeallocateFun& deallocFun
        ) {
        if (!mAllocator.contains(deviceID)) {
            mAllocator[deviceID] = {allocFun, deallocFun};
        }
    }

    AllocateFun allocFun(const DeviceID deviceID) {
        if (!mAllocator.contains(deviceID)) {
            throw std::runtime_error(std::format(
                "no allocate function is registered for this DeviceID: {}",
                deviceID));
        }
        return mAllocator[deviceID].mAllocFun;
    }

    DeallocateFun deallocFun(const DeviceID deviceID) {
        if (!mAllocator.contains(deviceID)) {
            throw std::runtime_error(std::format(
                "no deallocate function is registered for this DeviceID: {}",
                deviceID
                ));
        }
        return mAllocator[deviceID].mDeallocFun;
    }

private:
    struct Allocator {
        AllocateFun mAllocFun;
        DeallocateFun mDeallocFun;
    };

    std::unordered_map<DeviceID, Allocator> mAllocator;
};
}

#endif //CERYS_MEMORYMANAGER_080AB4275570491C9831938965AFCA24_H