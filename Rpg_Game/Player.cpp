#include "stdafx.h"
#include "Player.h"


//Initializer functions
void Player::initVariables()
{
	this->attackDuration = 1.0f;
}

void Player::initComponents()
{
	std::ifstream ifs("Config/PlayerAttributes.ini");
	if (ifs.is_open())
	{
		ifs >> exp;
		this->exp = exp;
	}
	ifs.close();

}


//constructor/destructor
Player::Player(float x,float y,sf::Texture& texture_sheet) : attacking(false)
{

	this->initVariables();
	this->initComponents();
	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite,70.f,10.f,65.f,130.f);
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createAnimationComponent( texture_sheet);
	this->createAttributeComponent(exp);
	
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 3, 0, 100, 70);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 6, 1, 100, 70);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 5, 2, 100, 70);
	this->animationComponent->addAnimation("ATTACK2", 6.f, 0, 3, 5, 3, 100, 70);
	this->animationComponent->addAnimation("ATTACK3", 4.f, 0, 4, 8, 4, 100, 70);
	this->animationComponent->addAnimation("ATTACK4", 8.f, 0, 5, 4, 5, 100, 70);
}

Player::~Player()
{
}

//accessors
AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//Functions
void Player::loseHP(const int hp)
{

	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::gainExp(const unsigned exp)
{

	this->attributeComponent->gainExp(exp);
	this->attributeComponent->updateLevel();


}

void Player::startAttackAnimation(const float& dt, int animationnumber)
{
	this->attacking = true;
	this->attackTimer.restart();
	this->animationnumber = animationnumber;
}


void Player::updateAnimation(const float& dt)
{

	this->movementComponent->update(dt);

	if(this->attacking)
	{

		// Play attack animation
		switch (this->animationnumber)
		{
		case 1:
			this->animationComponent->play("ATTACK", dt);
			break;
		case 2:
			this->animationComponent->play("ATTACK2", dt);
			break;
		case 3:
			this->animationComponent->play("ATTACK3", dt);
			break;
		case 4:
			this->animationComponent->play("ATTACK4", dt);
			break;
		default:
			break;
		}
	

		// Check if attack animation is complete
		if (this->attackTimer.getElapsedTime().asSeconds() >= this->attackDuration)
		{
			this->attacking = false; // Reset attacking state
		}
	}
	else if (this->movementComponent->getState(IDLE))
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

	else
	{
		this->animationComponent->play("IDLE", dt);
	}
	this->hitboxComponent->update();

}

void Player::update(const float& dt)
{

	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
