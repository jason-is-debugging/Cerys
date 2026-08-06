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
#ifndef CERYS_DEIVCE_9D8FD954CFDD4FA6AE3C68BC23C29DD7_H
#define CERYS_DEIVCE_9D8FD954CFDD4FA6AE3C68BC23C29DD7_H
#include <string>

#include "defines.h"
#include "MemoryManager.h"

namespace cerys::core::base {
class Device {
public:
    Device(
        DeviceID deviceID,
        AllocateFun allocateFun,
        DeallocateFun deallocFun);

    Pointer allocate(const SizeT size);

    void deallocate(Pointer ptr);

    std::string getName();

    DeviceID getDeviceID();

private:
    DeviceID mDeviceID;
    AllocateFun mAllocateFun;
    DeallocateFun mDeallocateFun;
};
}

#endif //CERYS_DEIVCE_9D8FD954CFDD4FA6AE3C68BC23C29DD7_H