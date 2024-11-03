#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

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

enum movement_states { IDLE = 0,MOVING, MOVING_LEFT, MOVING_RIGHT, MOVING_UP, MOVING_DOWN };

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;//how fast the player will reach the max velocity
	float deceleration;//how fast the player will stop

	sf::Vector2f velocity; //speed
	

	//Initializer functions

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//Accessors
    const sf:: Vector2f& getVelocity() const;
	//Functions
	const bool getState(const short unsigned state) const;

	void move(const float x, const float y, const float& dt);
	void update(const float& dt);
};

#endif // !MOVEMENTCOMPONENT_H
