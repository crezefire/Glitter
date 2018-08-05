#include <glitter/api-data-inl.h>
#include <glitter/gapi.h>
#include <glitter/vulkan/vulkan-helpers.h>

namespace glitt {

GAPI::GAPI(std::unique_ptr<GraphicsDeviceInterface> deviceInterface)
    : DeviceInterface(std::move(deviceInterface)) {}

gget::ErrorValue<GAPI> GAPI::CreateAndInit(void const* windowHandle, bool const enableDebugLayer) {
    auto [error, api] = Vulkan::Init(enableDebugLayer);

    if (error) return {std::move(error)};

    return {gget::Error::NoError, std::move(api)};
}

GAPI::~GAPI() {
    if (DeviceInterface) Vulkan::Destroy(DeviceInterface.get());
}
} // namespace glitt
