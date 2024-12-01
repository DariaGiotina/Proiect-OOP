

//Class that makes the game function like opening the window where the game is running 
//,updating the game objects and rendering them on the screen 

// Game.h
#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"



class Game
{

public:
	// Constructor / Destructor
	Game();
	virtual ~Game();

	// Functions

	//Regular
	void endApplication();

	//Update
	void updateDT();
	const bool running() const;
	void update();
	void updateSFMLEvents();

	//Render
	void render();

	//Core
	void run();

private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow* window;
	sf::Event ev;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states; //state is an abstract class so we need pointers in order to create objects
	//we use a stack so that we can put states over each other when we call them ex: if i want to pause my
	//game the pause state will be stacked upon my game state and when i want to unpause it i pop it off the top 

	std::map<std::string, int> supportedKeys; //map that holds the supported keys for the game

	float gridSize;

	//Initializer Functions
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initKeys();
	void initStateData();
	void initStates();

};

#endif // GAME_H