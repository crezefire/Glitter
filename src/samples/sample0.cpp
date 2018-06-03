#include <oss/window.h>

int main(int argc, char** argv) {

  const auto width  = 1280;
  const auto height = 720;

  const auto window = oss::Window::CreateOSWindow("GlitterSample0", width, height);

  while (oss::Window::RunOSUpdateLoop())
    ;

  return 0;
}
