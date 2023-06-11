#include "../include/Renderer.h"

void Renderer::draw(sf::RenderWindow& window, std::pair<sf::Sprite, sf::Sprite> backgrounds, sf::Sprite player, std::vector<Platform*> platforms)
{
	window.draw(backgrounds.first);
	window.draw(backgrounds.second);

	for (auto& p : platforms)
		window.draw(p->getPlatform());

	window.draw(player);
}