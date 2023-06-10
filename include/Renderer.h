#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Globals.h"



class Renderer
{
public:
	static void draw(sf::RenderWindow&, std::pair<sf::Sprite, sf::Sprite>);
private:
	Renderer() = default;
};

#endif