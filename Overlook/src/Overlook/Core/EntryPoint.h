#pragma once

#include "Overlook/Core/Base.h"
#ifdef  OL_PLATFORM_WINDOWS

extern Overlook::Application* Overlook::CreateApplication();

int main(int argc, char** argv)
{
	Overlook::Log::Init();
	OL_CORE_WARN("Initialized Log!");
	printf("Hello Overlook!!\n");
	auto app = Overlook::CreateApplication();
	app->Run();
	delete app;
}
#endif //  OL_PLATFORM_WINDOWS

