
// Game.h
#ifndef GAME_H
#define GAME_H


#include <iostream>
#include <ctime>
#include <vector>
#include<sstream>
#include<cstdlib>


#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{

public:
	// Constructor / Destructor
	Game();
	virtual ~Game();

	// Functions


	void updateDT();
	const bool running() const;
	void update();
	void updateSFMLEvents();
	void render();
	void run();

private:
	//Variables
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Clock dtClock;
	float dt;

	//Initializer Functions
	void initWindow();

};

#endif // GAME_H