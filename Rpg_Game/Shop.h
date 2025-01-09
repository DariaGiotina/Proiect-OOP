#ifndef SHOP_H
#define SHOP_H

#include "Inventory.h"
#include "Gui.h"
#include "Player.h"

class Shop
{
private:
    sf::Font& font;
    sf::Text menuText;
    sf::Texture idleTexture;
    sf::Texture hoverTexture;
    sf::Font font2;
    //Shop 
    sf::RectangleShape LisaShop;
    sf::Texture LisaShopTexture;

	sf::Text inventoryTextmoney;

    std::map<std::string, gui::Button*> buttons;

	bool mousePressed;

    //Functions
    void initVariables();
    void initItems();

public:
    std::map<std::string, Item*> items;
    Inventory* playerInventory;
	Player* player;

    Shop( sf::Font& font, Inventory* inventory, Player* player);
	virtual ~Shop();

	void addItem(Item* item);
    void removeItem(std::string& id, int quantity);


    std::map<std::string, gui::Button*>& getButtons();

    //Functions
    const bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float x, float y, const std::string text);
    
	void handlePurchase(const std::string& itemId,Player* player);
	void handleSell(const std::string& itemId, Player* player);

	void updateInventoryText();
	void updateItemSelection(const sf::Vector2i& mousePosWindow, Player* player);
    void update(const sf::Vector2i& mousePosWindow);

	void renderButtons(sf::RenderTarget& target);
	void renderInventoryText(sf::RenderTarget& target);
    void render(sf::RenderTarget& target,  const sf::Vector2f& position);
};

#endif // SHOP_H

