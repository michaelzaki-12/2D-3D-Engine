#pragma once
#include "PEPCH.h"
#include <memory>
#include "Application.h"
#include "Log.h"

#ifdef PR_PALTFORM_WINDOWS

extern Pirates::Application* Pirates::CreateApplication();

int main(int argc, char** argv) {
	Pirates::Log::Init();

	PR_PROFILE_BEGIN_SESSION("StartUp", "PIRATESPROFILE-Startup.json");
	auto app =  Pirates::CreateApplication();
	PR_PROFILE_END_SESSION();

	PR_PROFILE_BEGIN_SESSION("RUNTIME", "PIRATESPROFILE-RunTime.json");
	app->Run();
	PR_PROFILE_END_SESSION();

	PR_PROFILE_BEGIN_SESSION("ShutDown", "PIRATESPROFILE-ShutDown.json");
	delete app;
	PR_PROFILE_END_SESSION();

	}

#endif
