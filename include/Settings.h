#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "Globals.h"

class Settings
{
public:
	static void settings(bool&, float&, float&, float&, float&, float&, int&);
private:
	Settings() = default;
};

#endif