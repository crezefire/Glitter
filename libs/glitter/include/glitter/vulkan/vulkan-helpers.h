#pragma once

#include <gadget/error.h>
#include <glitter/api-data.h>

#include <memory>

namespace glitt {
struct Vulkan {
    static gget::ErrorValue<std::unique_ptr<GraphicsDeviceInterface>> Init(bool const enableDebugLayer);

    static void Destroy(GraphicsDeviceInterface* deviceInterface);
};
} // namespace glitt
