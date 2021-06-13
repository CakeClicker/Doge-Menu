#pragma once

#include "simpleini/SimpleIni.h"

namespace MenuConfig
{
	extern CSimpleIniA iniFile;
	extern bool bSafeAtIntervals;

	SI_Error ConfigInit();
	void ConfigRead();
	void ConfigSave();
	void ConfigResetHaxValues();
}



