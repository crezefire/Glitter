#include <oss/window.h>
#include <glitter/gapi.h>

int main(int argc, char** argv) {

    auto const width  = 1280;
    auto const height = 720;

    auto const window = oss::Window::CreateOSWindow("GlitterSample0", width, height);

    if (!window) return 0;

    auto const enableDebugLayer = true;

    auto [error, gapi] = glitt::GAPI::CreateAndInit(window.value().WindowsHandle, enableDebugLayer);

    if (error) return 0;

    while (oss::Window::RunOSUpdateLoop())
        ;

    return 0;
}
