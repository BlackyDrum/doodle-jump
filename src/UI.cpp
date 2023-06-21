#include "../include/UI.h"

bool UI::loadAssets()
{
	if (!m_font.loadFromFile("assets/fonts/DoodleJump.ttf") || !m_lostScreenTexture.loadFromFile("assets/textures/gameOverBackground1.png"))
		return false;

	return true;
}

void UI::setup()
{
	m_pause.setFont(m_font);
	m_pause.setString("Game Paused");
	m_pause.setCharacterSize(75);	
	m_pause.setFillColor(sf::Color::Black);
	m_pause.setOrigin(m_pause.getLocalBounds().left + m_pause.getLocalBounds().width / 2, m_pause.getLocalBounds().top + m_pause.getLocalBounds().height / 2);

	m_lostScreen.setTexture(m_lostScreenTexture);
	m_lostScreen.setOrigin(m_lostScreen.getLocalBounds().left + m_lostScreen.getLocalBounds().width / 2, m_lostScreen.getLocalBounds().top + m_lostScreen.getLocalBounds().height / 2);
}

void UI::update(sf::View view)
{
	m_pause.setPosition(view.getCenter());

	m_lostScreen.setPosition(view.getCenter());
}