#include "../include/Renderer.h"

void Renderer::draw(sf::RenderWindow& window, std::pair<sf::Sprite, sf::Sprite> backgrounds, sf::Sprite player, std::vector<Platform*> platforms, std::vector<Platform*> brokenPlatforms, std::vector<sf::Sprite*> projectiles)
{
	window.draw(backgrounds.first);
	window.draw(backgrounds.second);

	for (auto& p : platforms)
		window.draw(p->getPlatform());
	for (auto& p : brokenPlatforms)
		window.draw(p->getPlatform());

	for (auto& p : projectiles)
		window.draw(*p);

	window.draw(player);
}