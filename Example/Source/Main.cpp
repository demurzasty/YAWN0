#include <YAWN/YAWN.hpp>

#include <stdio.h>

using namespace YAWN;

int Main(int argc, char* argv[]) {
    MainLoop::Instance()->AddService(UI::Instance());

    return Application::Run();
}
