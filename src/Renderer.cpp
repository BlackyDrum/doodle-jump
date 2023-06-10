#include "../include/Renderer.h"

void Renderer::draw(sf::RenderWindow& window, std::pair<sf::Sprite, sf::Sprite> backgrounds)
{
	window.draw(backgrounds.first);
	window.draw(backgrounds.second);

}