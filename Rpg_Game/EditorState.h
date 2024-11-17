#ifndef EDITORSTATE_H
#define EDITORSTATE_H


#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"

class State;
class Gui;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
private:
	//Variables
	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pmenu;

	std::map<std::string, gui::Button*> buttons;

	TileMap* tileMap;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;
	gui::TextureSelector* textureSelector;

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
	void initText();
	void initKeybinds();
	void initPauseMenu();
	void initButtons();
	void initGui();
	void initTileMap();

public:
	EditorState(StateData* state_data);
	virtual ~EditorState();


	//functions
	void updateInput(const float& dt);
	void updateEditorInput(const float& dt);
	void updateButtons();
	void updateGui(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void renderGui(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif