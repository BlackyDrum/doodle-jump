#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Globals.h"

#include "Platform.h"

class Renderer
{
public:
	static void draw(sf::RenderWindow&, std::pair<sf::Sprite, sf::Sprite>, sf::Sprite, std::vector<Platform*>, std::vector<Platform*>);
private:
	Renderer() = default;
};

#endif