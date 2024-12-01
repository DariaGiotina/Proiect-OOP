#include "stdafx.h"
#include "PlayerGUI.h"


void PlayerGUI::initTextures()
{
	if (!this->hpBarBackTexture.loadFromFile("assets/game_gui/healthbar_back2.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD HP BAR BACK TEXTURE");
	}

	if (!this->hpBarInnerTexture.loadFromFile("assets/game_gui/healthbargreen_front.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD HP BAR INNER TEXTURE");
	}

	if (!this->expBarInnerTexture.loadFromFile("assets/game_gui/healthbar_front.png"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD HP BAR INNER TEXTURE");
	}
}

//Private functions
void PlayerGUI::initFont()
{
	if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
	{
		throw("ERROR::PLAYERGUI::COULD NOT LOAD FONT");
	}

}

void PlayerGUI::initHPBar()
{

	float width = 300.f;
	float height = 200.f;
	float x = 20.f;
	float y = 0.f;

	this->hpBarMaxWidth = 245.f;


	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(20);
	this->hpBarText.setFillColor(sf::Color::White);

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setPosition(x, y);
	this->hpBarBack.setTexture(&this->hpBarBackTexture);

	this->hpBarInner.setSize(sf::Vector2f(245.f, 85.f));
	this->hpBarInner.setTexture(&this->hpBarInnerTexture);
	this->hpBarInner.setPosition(x+35.f,y+35.f);


	this->hpBarText.setPosition(x + 137.f, y + 71.f);
}

void PlayerGUI::initExpBar()
{
	float x = 20.f;
	float y = 0.f;

	this->expBarMaxWidth = 245.f;

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(20);
	this->expBarText.setFillColor(sf::Color::White);

	this->expBarInner.setSize(sf::Vector2f(245.f, 85.f));
	this->expBarInner.setTexture(&this->expBarInnerTexture);
	this->expBarInner.setPosition(x + 38.f, y + 65.f);

	this->expBarText.setPosition(x + 137.f, y + 101.f);
}

//Constructor / Destructor
PlayerGUI::PlayerGUI(Player* player)
{
	this->player = player;

	this->initTextures();
	this->initFont();
	this->initHPBar();
	this->initExpBar();
}

PlayerGUI::~PlayerGUI()
{
}

//Functions
void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(
			this->hpBarMaxWidth * percent)),
			this->hpBarInner.getSize().y));

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " / " + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}

void PlayerGUI::updateExpBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(
				this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y));

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " / " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}


void PlayerGUI::update(const float& dt)
{
	this->updateHPBar();
	this->updateExpBar();
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::renderExpBar(sf::RenderTarget& target)
{
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHPBar(target);
	this->renderExpBar(target);
}
