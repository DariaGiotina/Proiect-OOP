#ifndef STATE_H
#define STATE_H


#include "Player.h"

//abstract class to keep the resources of the game and the base for other states
// like the main menu or game state
class State
{
private:

protected:

	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string,sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:

	//Constructor / Destructor
	State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	const bool& getQuit() const;
	
	//virtual functions

    void endState();
	virtual void updateMousePositions();
	virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};// we utilize the dt and target parameters to manage game logic and render it effectively



#endif // !STATE_H