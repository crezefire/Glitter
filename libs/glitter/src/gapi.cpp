#include <glitter/gapi.h>
#include <glitter/vulkan/vulkan-helpers.h>

namespace glitt {
GAPI GAPI::CreateAndInit(void const* windowHandle, const bool enableDebugLayer) {

    auto const api = Vulkan::Init(enableDebugLayer);

    if (!api) return {};

    return {};
}
} // namespace glitt
