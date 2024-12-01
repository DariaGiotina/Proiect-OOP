#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"

class MovementComponent;
class AnimationComponent;
class HitboxComponent;
class AttributeComponent;

class Entity
{
private:
	void initVariables();

protected: //objects can be accesed in the child class
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeComponent* attributeComponent;


public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const unsigned level);

	// Accesors
	virtual const sf::Vector2f& getPosition() const;

	//Modifiers
	virtual void setPosition(const float x, const float y);	

	//Functions
	virtual void move(const float x, const float y,const float& dt );
	void setScale(const float x, const float y); 

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget& target);
};

#endif