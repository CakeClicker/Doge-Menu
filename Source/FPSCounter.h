#pragma once
#include <string>
typedef unsigned long DWORD;

namespace _FPSCounter_ 
{
	class FPSCounter final 
	{
	protected:
		DWORD fpsValue;
		DWORD frameCounter;
		DWORD timer;

	public:
		FPSCounter();

		DWORD Get() const;
		std::string GetString() const;

		void Tick();
	};

	extern FPSCounter g_fpsCounter;

	void DisplayFPS();
	void DisplayFPSTick();
	extern bool bDisplayFps;
}

