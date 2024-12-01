#include "stdafx.h"
#include "SettingsState.h"


void SettingsState::initVariables() {
	if (!this->backgroundTexture.loadFromFile("assets/main_menu/mainmenu_background.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}

	// Load button textures
	if (!this->idleTextures["GAME_STATE"].loadFromFile("assets/main_menu/first_button.png") ||
		!this->hoverTextures["GAME_STATE"].loadFromFile("assets/main_menu/first_button_hover.png") ||
		!this->activeTextures["GAME_STATE"].loadFromFile("assets/main_menu/first_button_active.png") ||
		!this->idleTextures["LOAD_STATE"].loadFromFile("assets/main_menu/second_button.png") ||
		!this->hoverTextures["LOAD_STATE"].loadFromFile("assets/main_menu/second_button_hover.png") ||
		!this->activeTextures["LOAD_STATE"].loadFromFile("assets/main_menu/second_button_active.png") ||
		!this->idleTextures["SETTINGS_STATE"].loadFromFile("assets/main_menu/third_button.png") ||
		!this->hoverTextures["SETTINGS_STATE"].loadFromFile("assets/main_menu/third_button_hover.png") ||
		!this->activeTextures["SETTINGS_STATE"].loadFromFile("assets/main_menu/third_button_active.png") ||
		!this->idleTextures["EDITOR_STATE"].loadFromFile("assets/main_menu/fourth_button.png") ||
		!this->hoverTextures["EDITOR_STATE"].loadFromFile("assets/main_menu/fourth_button_hover.png") ||
		!this->activeTextures["EDITOR_STATE"].loadFromFile("assets/main_menu/fourth_button_active.png") ||
		!this->idleTextures["EXIT_STATE"].loadFromFile("assets/main_menu/fifth_button.png") ||
		!this->hoverTextures["EXIT_STATE"].loadFromFile("assets/main_menu/fifth_button_hover.png") ||
		!this->activeTextures["EXIT_STATE"].loadFromFile("assets/main_menu/fifth_button_active.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED TO LOAD BUTTON TEXTURES";
	}
}

void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));


	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}

}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();


}

void SettingsState::initButtons()
{
	sf::Color newGameColor = sf::Color::Black;
	

	this->buttons["EXIT_STATE"] = new gui::Button(60.f, 750.f, 500.f, 250.f,
		&this->font, "Quit", newGameColor,
		this->idleTextures["EXIT_STATE"], this->hoverTextures["EXIT_STATE"], this->activeTextures["EXIT_STATE"]
	);
}

SettingsState::SettingsState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


//Accessors

//Functions

void SettingsState::updateInput(const float& dt)
{


	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{

	}*/

}

void SettingsState::updateButtons()
{
	//Updates all the buttons in the state and handles their functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Quit this Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateInput(dt);
	this->updateButtons();


}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(*target);


	//REMOVE LATER
	/*sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(16);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);*/
}
