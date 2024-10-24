#ifndef STATE_H
#define STATE_H

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

//abstract class to keep the resources of the game and the base for other states
// like the main menu or game state
class State
{
private:
	sf::RenderWindow* window;
	std::vector<sf::Texture> textures;

public:

	//Constructor / Destructor
	State(sf::RenderWindow* window);
	virtual ~State();

	//virtual functions
	virtual void endState() = 0;

    virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};// we utilize the dt and target parameters to manage game logic and render it effectively



#endif // !STATE_H