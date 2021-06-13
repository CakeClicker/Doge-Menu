
#pragma once
#include "stdafx.h"
#include "MenuConfig.h"
#define Menu_Name "Doge"

void main() 
{
	char* name = SOCIALCLUB::_SC_GET_NICKNAME();

	bool ConsoleDetached = false;
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	notifyMap("Doge Menu Loaded");
	while (true) 
	{
		Menu::Name(name);
		Menu::Checks::Controlls();
		godmode(GODMODE);
		superrun(SUPERRUN);
		superjump(SUPERJUMP);
		superjumpv2(SUPERJUMPV2);
		invisible(INVISIBLE);
		neverwanted(NEVERWANTED);
		noragdoll(NORAGDOLL);
		pausetime(PAUSETIME);

		switch (Menu::Settings::currentMenu) {

		case mainmenu:
		{
			Menu::Title("Doge Menu");
			Menu::MenuOption("Self", self);
			Menu::MenuOption("Misc", Misc);
			Menu::MenuOption("World", World);
			Menu::MenuOption("Settings", settings);
			Menu::MenuOption("Update Log", update);
		}
		break;

		case self:
		{
			Menu::Title("Self Menu");
			Menu::Toggle("Godmode", GODMODE);
			Menu::Toggle("Super Run", SUPERRUN);
			Menu::Toggle("Super Jump", SUPERJUMP);
			Menu::Toggle("Super Jump V2", SUPERJUMPV2);
			Menu::Toggle("Invisible", INVISIBLE);
			Menu::Toggle("Never Wanted", NEVERWANTED);
			Menu::Toggle("No Ragdoll", NORAGDOLL);
		}
		break;

		case Misc:
		{
			Menu::Title("Misc");
		}
		break;

		case World:
		{
			Menu::Title("World");
			Menu::Toggle("Pause Time", PAUSETIME);
		}
		break;

		case settings:
		{
			Menu::Title("Settings"); 
			if (Menu::Option("Free Console"))
				if (ConsoleDetached == false) 
				{
					Log::Msg("Detaching Console...");
					FreeConsole();
					notifyBottom("Console Detached! You can now close the Console without getting Crashed!"),
						Log::Msg("Detached Console!");
					ConsoleDetached = true;
				}
				else if (ConsoleDetached == true) 
				{
					notifyBottom("Console already detached!");
				}
			if (Menu::Option("Exit GTA")) 
			{
				Log::Msg("Shutting Down GTA with Doge Menu...");
				exit(0);
			}
			
		}
		break;

		case update:
		{
			Menu::Title("Updates");
			Menu::MenuOption("Update 1.0",updateV1);
			Menu::MenuOption("Update 1.1", updateV1´1);
		}
		break;

		case updateV1:
		{
			Menu::Title("Version 1.0");
			Menu::Break("Update Log");
			Menu::AddSmallInfo("* ~r~SELF", 1);
			Menu::AddSmallInfo("* Added Godmode",2);
			Menu::AddSmallInfo("* Added Superjump + V2",3);
			Menu::AddSmallInfo("* Added Super Run", 4);
			Menu::AddSmallInfo("* Added Invisibility", 5);
			Menu::AddSmallInfo("* Added Never Wanted", 6);
			Menu::AddSmallInfo("* ~r~SETTINGS", 7);
			Menu::AddSmallInfo("* Added Free Console", 8);
			Menu::AddSmallInfo("* Added Exit GTA", 9);
			Menu::AddSmallInfo("* ~r~OTHER", 10);
			Menu::AddSmallInfo("* Added Injecting-Console", 11);
			Menu::AddSmallInfo("* Added More Hooks",12);
		}
		break;

		case updateV1´1:
		{
			Menu::Title("Version 1.1");
			Menu::Break("Update Log");
			Menu::AddSmallInfo("* ~r~SELF", 1);
			Menu::AddSmallInfo("* Added No Ragdoll", 2);
			Menu::AddSmallInfo("* ~r~OTHER", 3);
			Menu::AddSmallInfo("* Added INI Support", 4);
		}
		break;
		}
		Menu::End();
		WAIT(0);
	}
}

void ScriptMain() {
	srand(GetTickCount());

	main();
}