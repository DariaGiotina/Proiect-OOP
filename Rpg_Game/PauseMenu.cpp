#include "stdafx.h"
#include "PauseMenu.h"

void PauseMenu::initVariables()
{
	if (!this->backgroundTexture.loadFromFile("assets/pause_menu/pause_menu_better.png"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED TO LOAD PAUSE MENU BACKGROUND TEXTURE";
	}

	if 
		(!this->idleTexture.loadFromFile("assets/pause_menu/button_pause.png") ||
		!this->hoverTexture.loadFromFile("assets/pause_menu/button_pause.png") ||
		!this->activeTexture.loadFromFile("assets/pause_menu/button_pause_pressed.png") )
	{
		throw "ERROR::PAUSEMENUSTATE::FAILED TO LOAD BUTTON TEXTURES";
	}
}

void PauseMenu::initBackground(sf::RenderWindow& window)
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)));

	this->background.setTexture(&this->backgroundTexture);
}

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	this->initVariables();
	this->initBackground(window);


}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float x, float y, const std::string text)
{
	sf::Color textColor = sf::Color::White;
	this->buttons["RESUME"] = new gui::Button 
	   (670.f, 210.f, 600.f, 200.f,
		   &this->font, "RESUME", textColor,
		this->idleTexture, this->hoverTexture, this->activeTexture

	);
	
	this->buttons["SETTINGS"] = new gui::Button
	   (670.f,380.f, 600.f, 200.f,
		&this->font, "SETTINGS", textColor,
		this->idleTexture, this->hoverTexture, this->activeTexture

	);

	this->buttons["MAIN MENU"] = new gui::Button
	   (670.f, 560.f, 600.f, 200.f,
		&this->font, "MAIN MENU", textColor,
		this->idleTexture, this->hoverTexture, this->activeTexture

	);
	this->buttons["QUIT"] = new gui::Button
	    (670.f, 740.f, 600.f, 200.f,
		&this->font, "EXIT", textColor,
		this->idleTexture, this->hoverTexture, this->activeTexture

	);
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto& i : this->buttons)
	{
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	for(auto& i:this->buttons)
	{
		i.second->render(target);
	}
}


