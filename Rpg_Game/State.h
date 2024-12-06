#ifndef STATE_H
#define STATE_H


#include "Player.h"
#include "Enemy.h"
//abstract class to keep the resources of the game and the base for other states
// like the main menu or game state
#include "GraphicsSettings.h"


class Player;
class GraphicsSettings;
class State;

class StateData
{
public:
	StateData() {};

	//Variables
	float gridSize;
	sf::RenderWindow* window;
	GraphicsSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;
	//Player


};
class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<std::string,sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;



public:

	//Constructor / Destructor
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeyTime();
	
	//virtual functionscon

    void endState();
	void pauseState();
	void unpauseState();

	virtual void updateMousePositions(sf::View* view = NULL);
	virtual void updateKeyTime(const float& dt);
	virtual void updateInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};// we utilize the dt and target parameters to manage game logic and render it effectively



#endif // !STATE_H