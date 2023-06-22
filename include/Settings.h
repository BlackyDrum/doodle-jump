#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "Globals.h"

class Settings
{
public:
	Settings() = default;

	void settings(bool&, float&, float&, float&, float&, float&, int&, int, float[], int&, float&);

#ifdef _WIN32
	float getMemoryUse();
#else
	std::string readStatus(const std::string& key, std::string fileName);
#endif
private:
	sf::Clock m_frameClock;
};

#endif