#include "stdafx.h"
#include "EnemyState.h"


void EnemyState::initVariables()
{
	if (!this->backgroundTexture.loadFromFile("assets/enemy_bg/Cartoon_Forest_BG_04/Cartoon_Forest_BG_04.png"))
	{
		throw "ERROR::ENEMYSTATE::FAILED TO LOAD BACKGROUND TEXTURE";
	}
}

void EnemyState::initBackground()
{
	this->background.setSize(sf::Vector2f(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)));


	this->background.setTexture(&this->backgroundTexture);
}

void EnemyState::initKeybinds()
{
	std::ifstream ifs("Config/enemystate_keybinds.ini");
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

EnemyState::EnemyState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();

}

EnemyState::~EnemyState()
{

}

void EnemyState::updateInput(const float& dt)
{
}

void EnemyState::update(const float& dt)
{
	this->updateInput(dt);
}

void EnemyState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = this->window;
	}
	target->draw(this->background);
}
