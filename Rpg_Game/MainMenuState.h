#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H	

#include "GameState.h"
#include "Button.h"
class MainMenuState :
    public State
{
private:
	//Variables

	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	std::map<std::string, Button*> buttons;

	// Textures for buttons
	sf::Texture idleTexture;
	sf::Texture hoverTexture;
	sf::Texture activeTexture;

	// Map for button textures
	std::map<std::string, sf::Texture> idleTextures;
	std::map<std::string, sf::Texture> hoverTextures;
	std::map<std::string, sf::Texture> activeTextures;
	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();


	//functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !MAINMENYSTATE_H