#include "stdafx.h"
#include "Gui.h"

//Initializer functions
gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,sf::Color color,
	const sf::Texture& idleTexture, const sf::Texture& hoverTexture, const sf::Texture& activeTexture ) 
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));


	this->font = font;
	this->text.setFont(*this->font);
    this->text.setString(text);
	this->color = color;
	this->text.setFillColor(this->color);
	this->text.setCharacterSize(40);

	// Center the text within the button
	sf::FloatRect textRect = this->text.getLocalBounds();
	this->text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	this->text.setPosition(
		this->shape.getPosition().x + this->shape.getSize().x / 2.0f,
		this->shape.getPosition().y + this->shape.getSize().y / 2.0f
	);


	//this->idleColor = idleColor;
	//this->hoverColor = hoverColor;
	//this->activeColor = activeColor;


	this->idleTexture = idleTexture;
	this->hoverTexture = hoverTexture;
	this->activeTexture = activeTexture;

	this->shape.setTexture(&this->idleTexture);
}

gui::Button::~Button()
{
}

//Accessors
const bool gui::Button::isPressed() const
{

	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;

}

const std::string& gui::Button::getText() const
{
	return this->text.getString();
}

//Modifier
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

//Functions
void gui::Button::update(const sf::Vector2f& mousePos)
{
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Active
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState) {
	case BTN_IDLE:
		this->shape.setTexture(&this->idleTexture);
		break;
	case BTN_HOVER:
		this->shape.setTexture(&this->hoverTexture);
		break;
	case BTN_ACTIVE:
		this->shape.setTexture(&this->activeTexture);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}


//DropDownList class

void gui::DropDownList::initVariables()
{
	if
		(!this->idleTexture.loadFromFile("assets/pause_menu/button_pause.png") ||
			!this->hoverTexture.loadFromFile("assets/pause_menu/button_pause.png") ||
			!this->activeTexture.loadFromFile("assets/pause_menu/button_pause_pressed.png"))
	{
		throw "ERROR::DROPDOWNLIST::FAILED TO LOAD BUTTON TEXTURES";
	}
}

gui::DropDownList::DropDownList(sf::Font& font, std::string list[],unsigned nrOfElements, unsigned default_index=0)
	:font(font)
{
	for (size_t i = 0; i < nrOfElements; i++) 
	{
		this->list.push_back(
			new gui::Button(670.f, 210.f, 600.f, 200.f,
				&this->font, list[i], sf::Color::White,
				this->idleTexture, this->hoverTexture, this->activeTexture
			));
	}
	this->activeElement = new Button(*this->list[default_index]);
}


gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (auto *&i : this->list)
	{
		delete i;
	}
}

void gui::DropDownList::update(const sf::Vector2f& mousePos)
{
}
void gui::DropDownList::render(sf::RenderTarget& target)
{
}
