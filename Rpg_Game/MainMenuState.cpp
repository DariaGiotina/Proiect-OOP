#include "MainMenuState.h"

#include "GameState.h"  
#include <fstream> // Include the fstream header to fix incomplete type error

//Initializer functions
void MainMenuState::initVariables(){
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

void MainMenuState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));


	this->background.setTexture(&this->backgroundTexture);
}


void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initButtons()
{

	this->buttons["GAME_STATE"] = new Button(80, 76, 500, 250,
		&this->font, "New Game",
		this->idleTextures["GAME_STATE"], this->hoverTextures["GAME_STATE"], this->activeTextures["GAME_STATE"]

	);

	this->buttons["LOAD_STATE"] = new Button(70, 266, 500, 200,
		&this->font, "Load Game",
		this->idleTextures["LOAD_STATE"], this->hoverTextures["LOAD_STATE"], this->activeTextures["LOAD_STATE"]
		);

	this->buttons["SETTINGS_STATE"] = new Button(60, 416, 480, 250,
		&this->font, "Settings",
		this->idleTextures["SETTINGS_STATE"], this->hoverTextures["SETTINGS_STATE"], this->activeTextures["SETTINGS_STATE"]
		);

	this->buttons["EDITOR_STATE"] = new Button(70, 586, 480, 250,
		&this->font, "Editor",
		this->idleTextures["EDITOR_STATE"], this->hoverTextures["EDITOR_STATE"], this->activeTextures["EDITOR_STATE"]
	);

	this->buttons["EXIT_STATE"] = new Button(60, 750, 500, 250,
		&this->font, "Quit",
		this->idleTextures["EXIT_STATE"], this->hoverTextures["EXIT_STATE"], this->activeTextures["EXIT_STATE"]
		);
}

//Constructor / Destructor

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys,states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
	
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

void MainMenuState::updateInput(const float& dt)
{


	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
	{

	}*/
	
}

void MainMenuState::updateButtons()
{
	//Updates all the buttons in the state and handles their functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}
	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys,this->states));
	}

	//Quit this Game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

}

void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateInput(dt);
	this->updateButtons();


}

void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
	this->renderButtons(target);


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
