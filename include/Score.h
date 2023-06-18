#ifndef _SCORE_H_
#define _SCORE_H_

#include "Globals.h"

class Score
{
public:
	Score() = default;

	void setup();

	bool loadAssets();

	void update(sf::View, int);

	sf::Text getScore() const { return m_score; }
private:
	sf::Text m_score;

	sf::Font m_font;
};

#endif