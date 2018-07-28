#pragma once

#include <gadget/error.h>

namespace glitt {
struct Vulkan {
    static gget::Error Init(bool const enableDebugLayer);
};
} // namespace glitt
