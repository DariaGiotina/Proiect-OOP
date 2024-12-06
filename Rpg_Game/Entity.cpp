#include "stdafx.h"
#include "Entity.h"

void Entity::initVariables()
{
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->attributeComponent = NULL;
}

Entity::Entity()
{
	this->initVariables();

}

Entity::~Entity()
{
	if (this->hitboxComponent)
	{
		delete this->hitboxComponent;
		this->hitboxComponent = nullptr;
	}
	if (this->movementComponent)
	{
		delete this->movementComponent;
		this->movementComponent = nullptr;
	}
	if (this->animationComponent)
	{
		delete this->animationComponent;
		this->animationComponent = nullptr;
	}
	if (this->attributeComponent)
	{
		delete this->attributeComponent;
		this->attributeComponent = nullptr;
	}

}

//Component functions
void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite,offset_x,offset_y,width, height);

}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity,acceleration,deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const unsigned level)
{
	this->attributeComponent = new AttributeComponent(level);
}


// Functions
const sf::Vector2f& Entity::getPosition() const
{
	return this->sprite.getPosition();
}

void Entity::setPosition(const float x, const float y)
{
	
		this->sprite.setPosition(x, y);

}


 void Entity::move(const float dir_x, const float dir_y, const float& dt)
{
	if (this->movementComponent)
	{
		this->movementComponent->move(dir_x, dir_y,dt); //this is the speed of the player
	}
}

void Entity::setScale(const float x, const float y)
{
    this->sprite.setScale(x, y);
}


void Entity::update(const float& dt)
{

	
}

void Entity::render(sf::RenderTarget& target)
{
		target.draw(this->sprite);

		if (this->hitboxComponent)
		{
			this->hitboxComponent->render(target);
		}
		else
		{
			// Log a warning message indicating that hitboxComponent is NULL
			std::cerr << "Warning: hitboxComponent is NULL in Entity::render(). Ensure createHitboxComponent() is called before rendering." << std::endl;
		}
}
