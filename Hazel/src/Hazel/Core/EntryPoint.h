#pragma once

#include "Hazel/Core/Base.h"
#ifdef  HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	HZ_INFO("Hello info?");
	printf("Hello Hazel!!\n");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif //  HZ_PLATFORM_WINDOWS

