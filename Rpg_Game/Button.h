#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };//enum to keep track of the button states
class Button
{
private:
	short unsigned buttonState;

	bool pressed;
	bool hover;

	sf::RectangleShape shape;
	sf::Font* font;
	sf::Text text;
	sf::Texture idleTexture;
	sf::Texture hoverTexture;
	sf::Texture activeTexture;

	//sf::Color idleColor;
	//sf::Color hoverColor;
	//sf::Color activeColor;

	

public:
	Button(float x,float y, float width, float height,sf::Font*font, std::string text,
		const sf::Texture& idleTexture, const sf::Texture& hoverTexture, const sf::Texture& activeTexture);
	virtual ~Button();


	//Accessors
	const bool isPressed() const;

	//Functions
	void update(const sf::Vector2f mousePos);
	void render(sf::RenderTarget* target);

	
};

#endif // !BUTTON_H