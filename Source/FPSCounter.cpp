#include "stdafx.h"
#include "FPSCounter.h"
#include <Windows.h>
#include <string>
namespace _FpsCounter_
{
	FpsCounter::FpsCounter()
		: fpsValue(0), frameCounter(0), timer(GetTickCount())
	{
	}

	DWORD FpsCounter::Get() const
	{
		return fpsValue;
	}

	std::string FpsCounter::GetString() const
	{
		return std::to_string(fpsValue);
	}

	void FpsCounter::Tick()
	{
		frameCounter++;

		if (GetTickCount() - timer > 500) //0.5sec
		{
			// store frame count to fpsValue
			fpsValue = frameCounter * 2;

			// reset
			frameCounter = 0;
			timer = GetTickCount();
		}
	}

	FpsCounter g_fpsCounter;

	void DisplayFps()
	{
		g_fpsCounter.Tick();
		Game::Print::setupdraw(GTAfont::Impact, Vector2(0.4f, 0.4f), false, false, false);
		Game::Print::drawstring("~y~" + g_fpsCounter.GetString() + " FPS", 0.945f, 0.034f);
	}

	void DisplayFpsTick()
	{

	}

	bool bDisplayFps = false;

}
