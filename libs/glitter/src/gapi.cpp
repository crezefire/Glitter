#include <glitter/gapi.h>
#include <glitter/vulkan/vulkan-helpers.h>

namespace glitt {
GAPI::GAPI(char const* errorMessage)
    : ErrorCode(errorMessage) {}

GAPI GAPI::CreateAndInit(void const* windowHandle, const bool enableDebugLayer) {

    auto const api = Vulkan::Init(enableDebugLayer);

    if (!api) return {};

    return {};
}

const gget::Error& GAPI::GetError() const { return ErrorCode; }
} // namespace glitt
