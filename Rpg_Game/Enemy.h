#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.h"
class Enemy :
    public Entity
{
private:
	bool attacking;
	sf::Clock attackTimer;
	float attackDuration;

	void initVariables();
	void initComponents();
public:
	Enemy(float x, float y, sf::Texture& texture);
	virtual ~Enemy();

	//variables
	int hp;
	int hpMax;
	//accesors

	//Functions
	void loseHP(const int hp);
	void startAttackAnimation(const float& dt);
	virtual void updateAnimation(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget& target);
};

#endif // !ENEMY_H