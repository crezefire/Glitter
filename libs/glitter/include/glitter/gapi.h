#pragma once

#include <gadget/error.h>
#include <glitter/api-data.h>

#include <memory>

namespace glitt {

class GAPI {
    GAPI() = default;

    std::unique_ptr<GraphicsDeviceInterface> DeviceInterface;

public:
    GAPI(std::unique_ptr<GraphicsDeviceInterface> DeviceInterface);

    static gget::ErrorValue<GAPI> CreateAndInit(void const* windowHandle, bool const enableDebugLayer);

    GAPI(GAPI const&) = delete;
    GAPI(GAPI&&)      = delete;

    ~GAPI();
};
} // namespace glitt
