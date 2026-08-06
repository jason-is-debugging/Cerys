#ifndef CERYS_DEVICEREGISTRY_B044B03ED68645DEAC0F744968BF72D2_H
#define CERYS_DEVICEREGISTRY_B044B03ED68645DEAC0F744968BF72D2_H

#include <string_view>

#include "base/Registry.h"
#include "defines.h"
#include "Deivce.h"

namespace cerys::core::base {
    using DeviceRegistry = Registry<DeviceID>;

    inline constexpr std::string_view CpuDeviceName{"cpu"};
    inline constexpr std::string_view VectorizedDeviceName{"vectorized"};
    inline constexpr std::string_view CudaDeviceName{"cuda"};

    inline const DeviceID CpuDeviceID = DeviceRegistry::instance().registerName(CpuDeviceName);
    inline const DeviceID VectorizedDeviceID = DeviceRegistry::instance().registerName(VectorizedDeviceName);
    inline const DeviceID CudaDeviceID = DeviceRegistry::instance().registerName(CudaDeviceName);


    Device getDeviceByID(DeviceID deviceID);
    Device getDeviceByName(const std::string &deviceName);
}

#endif // CERYS_DEVICEREGISTRY_B044B03ED68645DEAC0F744968BF72D2_H
