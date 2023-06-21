#ifndef _UI_H_
#define _UI_H_

#include "Globals.h"

class UI
{
public:
	UI() = default;

	bool loadAssets();

	void setup();

	void update(sf::View);

	sf::Text getPause() const { return m_pause; }
private:
	sf::Font m_font;

	sf::Text m_pause;
};

#endif