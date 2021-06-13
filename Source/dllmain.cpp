// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "MenuConfig.h"
#include "Functions.h"

DWORD WINAPI HackThread( LPVOID lpParam, HMODULE hModule)
{
	//Create Console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	SetConsoleTitle(_T("Doge Menu"));

	const char* s3 = "                                 \n\
         $$$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$$\                       \n\
         $$  __$$\ $$  __$$\ $$  __$$\ $$  _____|                      \n\
         $$ |  $$ |$$ /  $$ |$$ / \__ |$$ |                            \n\
         $$ |  $$ |$$ |  $$ |$$ |$$$$\ $$$$$\                          \n\
         $$ |  $$ |$$ |  $$ |$$ |\_$$ |$$  __|                         \n\
         $$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |                            \n\
         $$$$$$$  | $$$$$$  |\$$$$$$  |$$$$$$$$\                       \n\
         \_______/  \______/  \______/ \________|                      \n\
                                                                       \n";

	//cout << s3 << endl;

	Log::Msg("%s\n", s3);

	Log::Msg("Injecting...");

	//CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadRainbowFader, NULL, 0, NULL);
	Log::Msg("About to load DogeConfig.ini...");
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadConfig, NULL, 0, NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
	Log::Msg("Loaded DogeConfig.ini!");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);


	//DisableThreadLibraryCalls(hModule);
	Hooking::Start((HMODULE)lpParam);
	return 0;
	

	while (true)
	{
		//do hack stuff

		if (GetAsyncKeyState(VK_END))
		{
			break;
		}
	}
	//unhook any hooks
	
	Hooking::Cleanup();
	//WSAUnhookBlockingHook();
	//if you have other threads, make sure they complete and stop executing
	

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	//FreeLibraryAndExitThread(static_cast<HMODULE>(hModule), 0);
	//ExitThread(0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


