#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

#include "State.h"

class EnemyState : public State
{
private:
	sf::RectangleShape background;
	sf::Texture backgroundTexture;

	//Functions
	void initVariables();
	void initBackground();
	void initKeybinds();
public:
	EnemyState(StateData* state_data);
	virtual ~EnemyState();

	void updateInput(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // 