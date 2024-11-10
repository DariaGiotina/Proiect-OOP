#ifndef SETTINGSSTATE
#define SETTINGSSTATE


#include "Gui.h"
#include "State.h"
class SettingsState :
    public State
{
private:
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
	void initButtons();
public:
	SettingsState(StateData* state_data);
	virtual ~SettingsState();


	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = nullptr);
};

#endif // !SETTINGSSTATE
