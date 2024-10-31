#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
class Entity
{
private:
	void initVariables();

protected: //objects can be accesed in the child class
	sf::Sprite sprite;

	MovementComponent* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity);

	// Functions
	virtual void setPosition(const float x, const float y);	
	virtual void move(const float& dt,const float x, const float y);
	void setScale(const float x, const float y); 

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif