#include "stdafx.h"
#include "MenuConfig.h"
#include "simpleini/\SimpleIni.h"
#include "ExePath.h"

CSimpleIniA MenuConfig::iniFile;
bool MenuConfig::bSafeAtIntervals = true;

SI_Error MenuConfig::ConfigInit() 
{
	MenuConfig::iniFile.SetUnicode(true);
	MenuConfig::iniFile.SetMultiLine(false);
	MenuConfig::iniFile.SetMultiKey(false);
	SetFileAttributesW(GetPathffW(Pathff::Main, false).c_str(), GetFileAttributes(GetPathffW(Pathff::Main, false).c_str()) & ~FILE_ATTRIBUTE_READONLY);
	return MenuConfig::iniFile.LoadFile((GetPathffA(Pathff::RootDir, true) + "DogeConfig.ini").c_str());
}

void MenuConfig::ConfigRead() 
{
	auto& ini = MenuConfig::iniFile;

	PCHAR section_self = "Self";
	GODMODE = ini.GetBoolValue(section_self, "Godmode", GODMODE);
	INVISIBLE = ini.GetBoolValue(section_self, "Invisible", INVISIBLE);
	NEVERWANTED = ini.GetBoolValue(section_self, "Never Wanted", NEVERWANTED);
	SUPERJUMP = ini.GetBoolValue(section_self, "Super Jump", SUPERJUMP);
	SUPERJUMPV2 = ini.GetBoolValue(section_self, "Super Jump V2", SUPERJUMPV2);
	NORAGDOLL = ini.GetBoolValue(section_self, "No Ragdoll", NORAGDOLL);
	SUPERRUN = ini.GetBoolValue(section_self, "Super Run", SUPERRUN);

	PCHAR section_world = "World";
	PAUSETIME = ini.GetBoolValue(section_world, "Pause Time", PAUSETIME);

}

void MenuConfig::ConfigSave() 
{
	auto& ini = MenuConfig::iniFile;

	PCHAR section_self = "self";
	

	ini.SetBoolValue(section_self, "Godmode", GODMODE);
	ini.SetBoolValue(section_self, "Invisible", INVISIBLE);
	ini.SetBoolValue(section_self, "Never Wanted", NEVERWANTED);
	ini.SetBoolValue(section_self, "Super Jump", SUPERJUMP);
	ini.SetBoolValue(section_self, "Super Jump V2", SUPERJUMPV2);
	ini.SetBoolValue(section_self, "No Ragdoll", NORAGDOLL);
	ini.SetBoolValue(section_self, "Super Run", SUPERRUN);

	PCHAR section_world = "World";
	ini.SetBoolValue(section_world, "Pause Time", PAUSETIME);

	ini.SaveFile((GetPathffA(Pathff::RootDir, true) + "DogeConfig.ini").c_str());
}
