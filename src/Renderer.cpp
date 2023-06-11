#include "../include/Renderer.h"

void Renderer::draw(sf::RenderWindow& window, std::pair<sf::Sprite, sf::Sprite> backgrounds, sf::Sprite player, sf::Sprite platform)
{
	window.draw(backgrounds.first);
	window.draw(backgrounds.second);

	window.draw(platform);

	window.draw(player);
}