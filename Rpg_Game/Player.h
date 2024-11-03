#ifndef PLAYER_H
#define PLAYER_H


#include "Entity.h"

class Player :
	public Entity
{
private:
	//Variables



	//Initializer functions
	void initVariables();
	void initComponents(); //initializes the components of the player


public:
	Player(float x, float y, sf::Texture& texture);//sf::Texture& t`exture
	virtual ~Player();

	//Functions

	virtual void update(const float& dt);
};

#endif // !PLAYER_H