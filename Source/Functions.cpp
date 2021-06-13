#include "stdafx.h"
#include <Windows.h>
#include <vector>
#include "types.h"
#include "MenuConfig.h"
#include <thread>
#include "ExePath.h"

//Features

//Self
bool GODMODE = 0;
bool SUPERRUN = 0;
bool SUPERJUMP = 0;
bool SUPERJUMPV2 =0;
bool INVISIBLE = 0;
bool NEVERWANTED = 0;
bool NORAGDOLL = 0;

//Misc
bool PAUSETIME = 0;
//Feature Functions

//Self
void godmode(bool toggle)
{
	if (toggle)
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), true);
		MenuConfig::ConfigSave();
	}
	else
	{
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), false);
		MenuConfig::ConfigSave();
	}
}
void superrun(bool toogle) 
{
	Player player = PLAYER::PLAYER_ID();
	if (toogle == true) 
	{
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1.49);
		MenuConfig::ConfigSave();
	}
	else if (toogle == false) 
	{
		PLAYER::SET_RUN_SPRINT_MULTIPLIER_FOR_PLAYER(player, 1);
		MenuConfig::ConfigSave();
	}
}
void superjump(bool toogle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (toogle == true)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"));
		MenuConfig::ConfigSave();
	}
}
void superjumpv2(bool toogle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (toogle)
	{
		GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(player);
		WEAPON::REMOVE_WEAPON_FROM_PED(playerPed, GAMEPLAY::GET_HASH_KEY("GADGET_PARACHUTE"));
		if (PED::IS_PED_JUMPING(playerPed))
		{
			ENTITY::APPLY_FORCE_TO_ENTITY(playerPed, true, 0, 0, 5, 0, 0, 0, true, true, true, true, false, true);
			MenuConfig::ConfigSave();
		}
	}
}
void invisible(bool toogle)
{
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (toogle)
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
		MenuConfig::ConfigSave();
	}
	else
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		MenuConfig::ConfigSave();
	}
}
void neverwanted(bool toogle) 
{
	Entity player = PLAYER::PLAYER_PED_ID();
	if (toogle)
	{
		PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
		PLAYER::SET_MAX_WANTED_LEVEL(0);

		PLAYER::SET_POLICE_IGNORE_PLAYER(player, true);
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, true);
		PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, true);
		PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, true);
		MenuConfig::ConfigSave();
	}
	else
	{
		PLAYER::SET_MAX_WANTED_LEVEL(5);
		PLAYER::SET_POLICE_IGNORE_PLAYER(player, false);
		PLAYER::SET_EVERYONE_IGNORE_PLAYER(player, false);
		PLAYER::SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(player, false);
		PLAYER::SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(player, false);
		MenuConfig::ConfigSave();

	}
}
void noragdoll(bool toogle) 
{
	Ped playerPed = PLAYER::PLAYER_PED_ID();
	if (toogle == true) 
	{
		PED::SET_PED_CAN_RAGDOLL(playerPed, false);
		MenuConfig::ConfigSave();
	}
	else if (toogle == false)
	{
		PED::SET_PED_CAN_RAGDOLL(playerPed, true);
		MenuConfig::ConfigSave();
	}
}

//World
void pausetime(bool toogle) 
{
	if (toogle) 
	{
		TIME::PAUSE_CLOCK(toogle);
		MenuConfig::ConfigSave();
	}
	else 
	{
		TIME::PAUSE_CLOCK(toogle);
		MenuConfig::ConfigSave();
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////


void ThreadConfig()
{
	//for (UINT8 configT = 0; MenuConfig::ConfigInit() < 0 && configT < 10; configT++)
	//std::this_thread::sleep_for(std::chrono::seconds(1));

	DWORD _programTick = 0U;

	std::this_thread::sleep_for(std::chrono::seconds(9));
	bool bConfigHasNotBeenRead = true;

	for (;;)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		_programTick++;

		if (_programTick % 30000 == 0 && MenuConfig::bSafeAtIntervals)
			MenuConfig::ConfigSave();

		if (bConfigHasNotBeenRead)
		{
			if (MenuConfig::ConfigInit() < 0)
			{
				Log::Error("Failed to load Config!");
			}
			else
			{
				MenuConfig::ConfigRead();
			}
			bConfigHasNotBeenRead = false;
		}

	}
}

std::ostream& operator<<(std::ostream& stream, std::wstring& text)
{
	stream << std::string(text.begin(), text.end());
	return stream;
}
std::wostream& operator<<(std::wostream& stream, std::string& text)
{
	stream << std::wstring(text.begin(), text.end());
	return stream;
}
char* CharKeyboard(char* windowName = "", int maxInput = 21, char* defaultText = "")
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(0, "", "", defaultText, "", "", "", maxInput);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return "";
	return GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT();
}
int NumberKeyboard() 
{
	GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(1, "", "", "", "", "", "", 10);
	while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0) WAIT(0);
	if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT()) return 0;
	return atof(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
}
void notifyleft(char* msg)
{
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
	UI::_DRAW_NOTIFICATION(2000, 1);
}

void TPtoCoord(float CoordsX, float CoordsY, float CoordsZ)
{
	int Handle = PLAYER::PLAYER_PED_ID();
	if (PED::IS_PED_IN_ANY_VEHICLE(Handle, 0)) { ENTITY::SET_ENTITY_COORDS(PED::GET_VEHICLE_PED_IS_IN(Handle, false), CoordsX, CoordsY, CoordsZ, 0, 0, 0, 1); }
	else { ENTITY::SET_ENTITY_COORDS(Handle, CoordsX, CoordsY, CoordsZ, 0, 0, 0, 1); }
}

void RequestControlOfid(Entity netid)
{
	int tick = 0;

	while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
		tick++;
	}
}

void RequestControlOfEnt(Entity entity)
{
	int tick = 0;
	while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
	{
		NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
		tick++;
	}
	if (NETWORK::NETWORK_IS_SESSION_STARTED()) 
	{
		int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
		RequestControlOfid(netID);
		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
	}
}

Vector3 rot_to_direction(Vector3*rot) {
	float radiansZ = rot->z*0.0174532924f;
	float radiansX = rot->x*0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ)))*(double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ))*(double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}

Vector3 add(Vector3*vectorA, Vector3*vectorB) {
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}

Vector3 multiply(Vector3*vector, float x) {
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}

float get_distance(Vector3*pointA, Vector3*pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba*y_ba;
	double x_2 = x_ba*x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}

float get_vector_length(Vector3*vector) {
	double x = (double)vector->x;
	double y = (double)vector->y;
	double z = (double)vector->z;
	return(float)sqrt(x*x + y*y + z*z);
}

//NOTIFICATIONS
/*
Colours:
~r~ = Red
~b~ = Blue
~g~ = Green
~y~ = Yellow
~p~ = Purple
~o~ = Orange
~c~ = Grey
~m~ = Dark Grey
~u~ = Black
~n~ = Skip Line
~s~ = White
~d~ = dark blue
~f~ = light blue
~l~ = black
~t~ = gray
~v~ = black

Fonts:
~italic~ = italic font
~bold~ = bold font
*/

char status_text[2048] = { 0 };
void update_status_text()
{
	if (GetTickCount() < 2500)
	{
		UI::SET_TEXT_FONT(0);
		UI::SET_TEXT_SCALE(0.55f, 0.55f);
		UI::SET_TEXT_COLOUR(255, 255, 255, 255);
		UI::SET_TEXT_WRAP(0.0f, 1.0f);
		UI::SET_TEXT_CENTRE(1);
		UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(status_text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(0.5, 0.5);
	}
}

void menu_beep()
{
	AUDIO::PLAY_SOUND_FRONTEND(-1, "BACK", "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
}


void notifyBottom(char * fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);

	UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	UI::END_TEXT_COMMAND_PRINT(4000, 1);
}	void notifyBottom(std::string str) { notifyBottom(&str[0]); }

void notifyMap(char * fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	char buff2[2048] = { 0 };
	sprintf_s(buff2, "%s", buf);

	UI::SET_TEXT_OUTLINE();
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);
}	void notifyMap(std::string str) { notifyMap(&str[0]); }

void notifyCenter(char * fmt, ...)
{
	char buf[2048] = { 0 };
	va_list va_alist;

	va_start(va_alist, fmt);
	vsprintf_s(buf, fmt, va_alist);
	va_end(va_alist);

	sprintf_s(status_text, "%s", buf);
}	void notifyCenter(std::string str) { notifyCenter(&str[0]); }

void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
{
	GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
}


void draw_menu_line(string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText)
{
	int text_col[4] = { 255, 255, 255, 255 },
		rect_col[4] = { 0, 0, 0, 80 };
	float text_scale = 0.30f;
	int font = 0;
	bool outline = true;
	bool dropshadow = true;
	if (active)
	{
		outline = false;
		dropshadow = true;
		text_col[0] = 0;
		text_col[1] = 0;
		text_col[2] = 0;
		text_col[3] = 255;
		rect_col[0] = 255;
		rect_col[1] = 255;
		rect_col[2] = 255;
		rect_col[3] = 80;
		if (rescaleText)text_scale = 0.30f;
	}

	if (title)
	{
		outline = true;
		dropshadow = true;
		text_col[0] = 255;
		text_col[1] =255;
		text_col[2] = 255;
		text_col[3] = 255;
		rect_col[0] = 93;
		rect_col[1] = 182;
		rect_col[2] = 229;
		rect_col[2] = 255;
		if (rescaleText)text_scale = 0.36f;
		font = 0;
	}
	int screen_w, screen_h;
	GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);
	textLeft += lineLeft;
	float lineWidthScaled = lineWidth / (float)screen_w;
	float lineTopScaled = lineTop / (float)screen_h;
	float textLeftScaled = textLeft / (float)screen_w;
	float lineHeightScaled = lineHeight / (float)screen_h;
	float lineLeftScaled = lineLeft / (float)screen_w;
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	if (outline) { UI::SET_TEXT_EDGE(1, 255, 215, 0, 255); }
	if (dropshadow) { UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255); }
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((LPSTR)caption.c_str());
	UI::END_TEXT_COMMAND_DISPLAY_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(0.0, text_scale);
	UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
	UI::SET_TEXT_CENTRE(0);
	if (outline) { UI::SET_TEXT_EDGE(1, 255, 215, 0, 255); }
	if (dropshadow) { UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255); }
	UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((LPSTR)caption.c_str());
	int num25 = UI::_GET_TEXT_SCREEN_LINE_COUNT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));
	draw_rect(lineLeftScaled, lineTopScaled + (0.00278f),
	lineWidthScaled, ((((float)(num25)* UI::_GET_TEXT_SCALE_HEIGHT(text_scale, 0)) + (lineHeightScaled * 1.0f)) + 0.005f),
	rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
}