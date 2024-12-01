#ifndef PLAYER_H
#define PLAYER_H


#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables
	// 
	//Initializer functions
	void initVariables();
	void initComponents(); //initializes the components of the player


public:
	Player(float x, float y, sf::Texture& texture);//sf::Texture& t`exture
	virtual ~Player();

	//accessors
	AttributeComponent* getAttributeComponent();

	//Functions
	void loseHP(const int hp);
	void gainHP(const int hp);
	void gainExp(const unsigned exp);
	virtual void updateAnimation(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif // !PLAYER_H