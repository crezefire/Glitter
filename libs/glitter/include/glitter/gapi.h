#pragma once

#include <glitter/api-data.h>
#include <gadget/error.h>

namespace glitt {
class GAPI {
    bool IsInitialised{false};

    GAPI() = default;

    public:
    static GAPI CreateAndInit(void const* windowHandle, bool const enableDebugLayer);

    GAPI(const GAPI&) = delete;
    GAPI(GAPI&&)      = delete;

    explicit operator bool() const { return IsInitialised; }
};
} // namespace glitt
