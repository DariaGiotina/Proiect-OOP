#include "stdafx.h"
#include "Player.h"


//Initializer functions
void Player::initVariables()
{

}

void Player::initComponents()
{
	

}


//constructor/destructor
Player::Player(float x,float y,sf::Texture& texture_sheet)
{

	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite,70.f,10.f,65.f,130.f);
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createAnimationComponent( texture_sheet);
	
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0, 100, 70);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 6, 1, 100, 70);
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 2, 5, 2, 100, 70);
}

Player::~Player()
{
}

//Functions
void Player::update(const float& dt)
{

	this->movementComponent->update(dt);

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(2.f, 2.f);
		this->animationComponent->play("WALK", dt,this->movementComponent->getVelocity().x,this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent -> getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(100.f, 0.f);
		this->sprite.setScale(-2.f, 2.f);
		this ->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt,this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt,this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	this->hitboxComponent->update();

}
