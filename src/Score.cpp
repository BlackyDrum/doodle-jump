#include "../include/Score.h"

bool Score::loadAssets()
{
	if (!m_font.loadFromFile("assets/fonts/DoodleJump.ttf"))
		return false;

	return true;
}

void Score::setup()
{
	m_score.setString("0");
	m_score.setCharacterSize(50);
	m_score.setFont(m_font);
	m_score.setFillColor(sf::Color::Black);
}

void Score::update(sf::View view, int score)
{
	int offset = 5;

	m_score.setPosition(offset, view.getCenter().y - SCREEN_HEIGHT / 2 - offset);
	m_score.setString(std::to_string(score * -1));
}