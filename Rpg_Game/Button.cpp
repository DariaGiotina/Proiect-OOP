#include "Button.h"

//Initializer functions
Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	const sf::Texture& idleTexture, const sf::Texture& hoverTexture, const sf::Texture& activeTexture )
{
	this->buttonState = BTN_IDLE;

	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));


	this->font = font;
	this->text.setFont(*this->font);
    this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(36);

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

Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{

	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;

}

//Functions
void Button::update(const sf::Vector2f mousePos)
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

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}


