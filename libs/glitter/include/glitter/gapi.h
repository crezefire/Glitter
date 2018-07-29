#pragma once

#include <gadget/error.h>

namespace glitt {
class GAPI {
    GAPI() = default;
    GAPI(char const* errorMessage);

    gget::Error ErrorCode;

public:
    static GAPI CreateAndInit(void const* windowHandle, bool const enableDebugLayer);

    GAPI(const GAPI&) = delete;
    GAPI(GAPI&&)      = delete;

    const gget::Error& GetError() const;
};
} // namespace glitt
