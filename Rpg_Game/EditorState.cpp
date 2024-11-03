#include "EditorState.h"
#include "GameState.h"  
#include <fstream> // Include the fstream header to fix incomplete type error

//Initializer functions
void EditorState::initVariables() {


	// Load button textures
	/*if (!this->idleTextures["GAME_STATE"].loadFromFile("assets/main_menu/first_button.png") ||*/

}

void EditorState::initBackground()
{

}


void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT"); //exits the program and shows the error message
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini");
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

void EditorState::initButtons()
{

	//this->buttons["GAME_STATE"] = new Button(80, 76, 500, 250,
	//	&this->font, "New Game",
	//	this->idleTextures["GAME_STATE"], this->hoverTextures["GAME_STATE"], this->activeTextures["GAME_STATE"]

	//);

	
}

//Constructor / Destructor

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

}

EditorState::~EditorState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

void EditorState::updateInput(const float& dt)
{

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();

}

void EditorState::updateButtons()
{
	//Updates all the buttons in the state and handles their functionality
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();

	this->updateInput(dt);
	this->updateButtons();


}

void EditorState::renderButtons(sf::RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
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
