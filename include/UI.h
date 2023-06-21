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
	
	bool restart(sf::RenderWindow&);

	sf::Text getPause() const { return m_pause; }
	sf::Sprite getLostScreen() const { return m_lostScreen; }
private:
	sf::Font m_font;

	sf::Text m_pause;

	sf::Texture m_lostScreenTexture;
	sf::Sprite m_lostScreen;
};

#endif