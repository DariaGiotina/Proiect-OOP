#ifndef MOVEMENTCOMPONENT_H
#define MOVECOMPONENT_H

#include <vector>
#include <iostream>
#include <ctime>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <map>
#include <stack>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;

	sf::Vector2f velocity; //speed
	sf::Vector2f acceleration;//how fast the player will reach the max velocity
	sf::Vector2f deceleration;//how fast the player will stop

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity);
	virtual ~MovementComponent();

	//Accessors
    const sf:: Vector2f& getVelocity() const;

	//Functions
	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

#endif // !MOVEMENTCOMPONENT_H
