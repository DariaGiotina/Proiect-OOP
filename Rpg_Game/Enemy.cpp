#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	this->hpMax = 10;
	this->hp = this->hpMax;
	this->attackDuration = 2.5f;
}

void Enemy::initComponents()
{
}

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents();
	this->createMovementComponent(200.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

	this->setPosition(x, y);
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 6, 0, 80, 64);
	this->animationComponent->addAnimation("ATTACK", 10.f, 0, 1, 9, 1, 80, 64);
	//this->animationComponent->addAnimation("Hit", 10.f, 0, 2, 4, 2, 80, 64);
}

Enemy::~Enemy()
{
}



void Enemy::loseHP(const int hp)
{
	this->hp -= hp;

	if (this->hp < 0)
		this->hp = 0;
}

void Enemy::startAttackAnimation(const float& dt)
{
	this->attacking = true;
	this->attackTimer.restart();
}

void Enemy::updateAnimation(const float& dt)
{

	if (this->attacking)
	{
		// Play attack animation
		this->animationComponent->play("ATTACK", dt);

		// Check if attack animation is complete
		if (this->attackTimer.getElapsedTime().asSeconds() >= this->attackDuration)
		{
			this->attacking = false; // Reset attacking state
		}
	}
	else
	{
		this->animationComponent->play("IDLE", dt);
	}
}

void Enemy::update(const float& dt)
{

	this->movementComponent->update(dt);
	this->updateAnimation(dt);

}

void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
