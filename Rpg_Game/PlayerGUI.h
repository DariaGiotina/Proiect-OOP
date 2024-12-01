#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "stdafx.h"
#include "Player.h"

class Player;
class sf::RectangleShape;

class PlayerGUI
{
private:
	Player* player;

	sf::Font font;

	//EXP Bar

	//HP Bar
	std::string hpBarString;
	sf::Text hpBarText;

	std::string expBarString;
	sf::Text expBarText;

	float hpBarMaxWidth;
	sf::RectangleShape hpBarBack;
	sf::RectangleShape hpBarInner;

	sf::RectangleShape expBarInner;
	float expBarMaxWidth;

	sf::Texture hpBarBackTexture;
	sf::Texture hpBarInnerTexture;
	sf::Texture expBarInnerTexture;

	void initTextures();
	void initFont();
	void initHPBar();
	void initExpBar();
public:
	PlayerGUI(Player* player);
	virtual ~PlayerGUI();

	//Functions
	void updateHPBar();
	void updateExpBar();
	void update(const float& dt);

	void renderHPBar(sf::RenderTarget& target);
	void renderExpBar(sf::RenderTarget& target);
	void render(sf::RenderTarget& target);
};

#endif // !PLAYERGUI_H
