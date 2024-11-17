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


//TextureSelector class


//Functions
void gui::TextureSelector::initVariables()
{
	if
		(!this->idleTexture.loadFromFile("assets/pause_menu/button_pause.png") ||
			!this->hoverTexture.loadFromFile("assets/pause_menu/button_pause.png") ||
			!this->activeTexture.loadFromFile("assets/pause_menu/button_pause_pressed.png"))
	{
		throw "ERROR::DROPDOWNLIST::FAILED TO LOAD BUTTON TEXTURES";
	}
}

gui::TextureSelector::TextureSelector(float x, float y, float width, float height,float gridSize,
	const sf::Texture* texture_sheet, sf::Font& font) :
	keyTimeMax(1.f), keyTime(0.f)

{
	this->initVariables();
	this->gridSize = gridSize;
	this->active = false;
	this->hidden = false;
	float offset = 60.f;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->bounds.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
	}
	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, this->sheet.getGlobalBounds().width, this->bounds.getGlobalBounds().height));
	}

	this->selector.setPosition(x + offset, y);
	this->selector.setSize(sf::Vector2f(gridSize,gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = static_cast<int>(gridSize);
	this->textureRect.height = static_cast<int>(gridSize);

	sf::Color newGameColor = sf::Color::White;

	this->hide_btn = new gui::Button(
		x+60.f, y+200.f, 200.f, 100.f,
		&font, "Hide", newGameColor,
		this->idleTexture, this->hoverTexture, this->activeTexture
	);
}

gui::TextureSelector::~TextureSelector()
{
	delete this->hide_btn;
}

//Accessors

const bool& gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

//Functions
const bool gui::TextureSelector::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::TextureSelector::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
		this->keyTime += 10.f * dt;
}

void gui::TextureSelector::update(const sf::Vector2i& mousePosWindow,const float& dt)
{

	this->updateKeyTime(dt);
	this->hide_btn->update(static_cast<sf::Vector2f>(mousePosWindow));

	if (this->hide_btn->isPressed() && this->getKeyTime())
	{
		if (this->hidden)
			this->hidden = false;
		else
			this->hidden = true;
	}

	this->hide_btn->update(static_cast<sf::Vector2f>(mousePosWindow));
	if (!this->hidden) {

	

	if (this->bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
		this->active = true;
	else
		this->active = false;

	if (this->active)
		{
		this->mousePosGrid.x = (mousePosWindow.x - static_cast<int>(this->bounds.getPosition().x)) / static_cast<unsigned>(this->gridSize);
		this->mousePosGrid.y = (mousePosWindow.y - static_cast<int>(this->bounds.getPosition().y)) / static_cast<unsigned>(this->gridSize);
		this->selector.setPosition(
			this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
			this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize);

		//Update texture rectangle
		this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->bounds.getPosition().x);
		this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::render(sf::RenderTarget& target)
{
	

	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);

		if (this->active)
			target.draw(this->selector);
	}
	this->hide_btn->render(target);
}
