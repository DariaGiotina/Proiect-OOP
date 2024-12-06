#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H	

#include "GameState.h"
#include "Gui.h"
#include "EditorState.h"
#include "SettingsState.h"


class MainMenuState :
    public State
{
private:
	//Variables

	sf::RectangleShape background;
	sf::Texture backgroundTexture;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;


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
	void initGui();
	void initButtons();

public:
	MainMenuState(StateData* state_data);
	virtual ~MainMenuState();


	//functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !MAINMENYSTATE_H