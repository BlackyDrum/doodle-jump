#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "Globals.h"

class Renderer
{
public:
	static void draw(sf::RenderWindow&);
private:
	Renderer() = default;
};

#endif