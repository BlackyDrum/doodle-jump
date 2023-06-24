#ifndef _SCORE_H_
#define _SCORE_H_

#include "Globals.h"

class Score
{
public:
	Score(int highscore)
		: m_highScoreI{ highscore } {};

	void setup();

	bool loadAssets();

	void update(sf::View, int);

	sf::Text& getScore() { return m_score; }
	sf::Text& getHighScore() { return m_highscore; }
	int getHighScoreInt() const { return m_highScoreI; }

	void setHighScore(int highscore) { m_highScoreI = highscore; }
private:
	sf::Text m_score, m_highscore;
	
	int m_highScoreI;

	sf::Font m_font;
};

#endif