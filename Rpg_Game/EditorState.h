#ifndef EDITORSTATE_H
#define EDITORSTATE_H


#include "State.h"
#include "Button.h"

class EditorState :
    public State
{
private:
private:
	//Variables
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
	EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~EditorState();


	//functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget* target = nullptr);
	void render(sf::RenderTarget* target = nullptr);
};

#endif