#ifndef ENTITY_H
#define ENTITY_H

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
class Entity
{
private:
	

protected: //objects can be accesed in the child class
	sf::RectangleShape shape; //placeholder for the entity
	float movementSpeed; //speed of the entity

public:
	Entity();
	virtual ~Entity();

	// Functions
	virtual void move(const float& dt,const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif