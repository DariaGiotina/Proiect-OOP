#ifndef GUI_H
#define GUI_H

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };//enum to keep track of the button states

namespace gui{
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
	sf::Color color;


public:
	Button(float x, float y, float width, float height, sf::Font* font, std::string text,sf::Color color,
		const sf::Texture& idleTexture, const sf::Texture& hoverTexture, const sf::Texture& activeTexture);
	virtual ~Button();


	//Accessors
	const bool isPressed() const;
	const std::string& getText() const;

	//Modifier
	void setText(const std::string text);	

	//Functions
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);

	
};

//DropDownList class

class DropDownList 
{
	private:
		 sf::Font& font;
		 gui::Button* activeElement;
		 std::vector<gui::Button*> list;

		 sf::Texture idleTexture;
		 sf::Texture hoverTexture;
		 sf::Texture activeTexture;

		 //Initializer functions
		 void initVariables();

	public: 
		DropDownList(sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index);
		~DropDownList();

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
};

}
#endif // !BUTTON_H