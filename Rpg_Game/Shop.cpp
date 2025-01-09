#include "stdafx.h"
#include "Shop.h"

void Shop::initVariables()
{
    if (!this->idleTexture.loadFromFile("assets/main_menu/first_button.png"))
    {
        throw("ERROR::SHOP::COULD NOT LOAD SHOP BUTTON TEXTURE");
    }

    if (!this->hoverTexture.loadFromFile("assets/main_menu/first_button_active.png"))
    {
        throw("ERROR::SHOP::COULD NOT LOAD SHOP BUTTON TEXTURE");
    }

    if (!this->LisaShopTexture.loadFromFile("assets/inventory/gigapixel-shop.png"))
    {
        throw("ERROR::SHOP::COULD NOT LOAD SHOP TEXTURE");
    }

    if (!this->font2.loadFromFile("Fonts/Rundeck.ttf"))
    {
        throw("ERROR::GAMESTATE::COULD NOT LOAD FONT2"); //exits the program and shows the error message
    }


    this->inventoryTextmoney.setFont(this->font2);
    this->inventoryTextmoney.setCharacterSize(20);
    this->inventoryTextmoney.setFillColor(sf::Color(96, 68, 93, 255));
    this->inventoryTextmoney.setPosition(530.f, 917.f);
    this->inventoryTextmoney.setString(sf::String(std::to_string(this->player->getAttributeComponent()->money)));
}

void Shop::initItems()
{
    Item* healthPotion = new Item("potion_001", "Health Potion", 5, true, "assets/MF_Items/MF_Items_potions_9.png",10);
    this->addItem(healthPotion);

	Item* manaPotion = new Item("potion_002", "Mana Potion", 1, true, "assets/MF_Items/MF_Items_potions_11.png",15);
	this->addItem(manaPotion);

    Item* FlowerLoot = new Item("flowerPlantLoot", "Flower Petals", 1, true, "assets/MF_Items/MF_Items_flower_4.png",5);
    Item* MushroomLoot = new Item("mushroomLoot", "Mushroom Spores", 1, true, "assets/MF_Items/MF_Items_mushroom_1.png",3);

    Item* Cheese = new Item("cheese", "Cheese Slice", 1, true, "assets/MF_Items/MF_Items_farm_3.png",5);
	this->addItem(Cheese);

    Item* Egg = new Item("egg", "Egg", 1, true, "assets/MF_Items/MF_Items_farm_6.png",2);
    this->addItem(Egg);

    Item* RedRing = new Item("redring", "Red Ring", 1, true, "assets/MF_Items/MF_Items_precious_5.png",20);
    this->addItem(RedRing);

}


Shop::Shop(sf::Font& font, Inventory* inventory,Player* player)
	: font(font), playerInventory(inventory), player(player), mousePressed(false)
{
   
	this->initVariables();
	this->initItems();


    this->LisaShop.setSize(sf::Vector2f(1100.f, 1100.f));
    this->LisaShop.setTexture(&this->LisaShopTexture);
    this->LisaShop.setPosition(800.f, -30.f);
}

Shop::~Shop()
{
    auto it = this->buttons.begin();
    for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
    {
        delete it->second;
    }

	for (auto& pair : items) {
		delete pair.second;
	}

}



void Shop::addItem(Item* item)
{
    if (item->getIsStackable() && items.find(item->getId()) != items.end()) {
        items[item->getId()]->setQuantity(items[item->getId()]->getQuantity() + 1);
        delete item; // Free memory for the incoming item
    }
    else {
        items[item->getId()] = item; // Store the new item
    }
}

void Shop::removeItem(std::string& id, int quantity)
{

    auto it = items.find(id);

    if (it != items.end()) {
        Item* item = it->second;
        item->setQuantity(item->getQuantity() - quantity);

        if (item->getQuantity() <= 0) {
            delete item; // Free memory
            items.erase(it); // Remove from the map
        }
    }
    else {
        std::cout << "Item not found in shop.\n";
    }
}


std::map<std::string, gui::Button*>& Shop::getButtons()
{
    return this->buttons;
}

const bool Shop::isButtonPressed(const std::string key)
{
    return this->buttons[key]->isPressed();
}


void Shop::addButton(const std::string key, float x, float y, const std::string text)
{

        sf::Color textColor = sf::Color::White;

        this->buttons[key] = new gui::Button
        (x, y, 350.f, 175.f,
            &this->font, text, textColor,
            this->idleTexture, this->hoverTexture, this->hoverTexture

        );

        this->buttons[key] = new gui::Button
        (x, y, 350.f, 175.f,
            &this->font, text, textColor,
            this->idleTexture, this->hoverTexture, this->hoverTexture

        );
}

void Shop::handlePurchase(const std::string& itemId, Player* player)
{
	std::cout << itemId << std::endl;
    auto it = items.find(itemId);
    if (it != items.end()) {
        Item* item = it->second;

        if (player->getAttributeComponent()->getMoney() >= item->getPrice()) {
            player->loseMoney(item->getPrice());  
            playerInventory->addItem(new Item(*item)); 


            // Optional: Remove item from shop if non-stackable or decrease quantity
            if (item->getIsStackable() && item->getQuantity() == 1) {
                std::string itemId2 = itemId;
                removeItem(itemId2, item->getQuantity());

            }
            else {
                std::string itemId2 = itemId;
                removeItem(itemId2, 1); // Decrease stack by 1
            }
        }
        else {
            std::cout << "Not enough gold to buy " << item->getName() << ".\n";
        }
    }
    else {
        std::cout << "Item not found in shop handle purchase.\n";
    }
}

void Shop::handleSell(const std::string& itemId, Player* player)
{
    auto inventoryItem = playerInventory->getItems().find(itemId); // Access player's inventory items
    if (inventoryItem != playerInventory->getItems().end()) {
        Item* item = inventoryItem->second;

        // Add gold to the player's balance (you can adjust the selling price formula)
        int sellPrice = item->getPrice() / 2; // Example: sell for half the price
        player->gainMoney(sellPrice);

        // Add the item to the shop's inventory or increase its quantity
        if (item->getIsStackable() && items.find(itemId) != items.end()) {
            items[itemId]->setQuantity(items[item->getId()]->getQuantity() + 1);
        }
        else {
            addItem(new Item(*item)); // Clone the item and add to the shop
        }

        // Remove the item from the player's inventory or decrease its quantity
        std::string itemId2 = itemId;
        playerInventory->removeItem(itemId2, 1);

    }
    else {
        std::cout << "Item not found in player's inventory.\n";
    }
}

void Shop::updateInventoryText()
{
    this->inventoryTextmoney.setString(sf::String(std::to_string(this->player->getAttributeComponent()->money)));
}

void Shop::updateItemSelection(const sf::Vector2i& mousePosWindow, Player* player)
{

	/*std::cout << "Mouse Position: " << mousePosWindow.x << " " << mousePosWindow.y << std::endl;*/
    float slotSize = 85.0f;
    float padding = 5.0f;

    int cols = 4; // Number of columns
    int currentSlot = 0;

    for (auto& pair : items) {
        const Item* item = pair.second;
        int row = currentSlot / cols;
        int col = currentSlot % cols;

        float x = 1195.f + col * (slotSize + padding);  
        float y = 342 + row * (slotSize + padding);

        sf::FloatRect itemBounds(x, y, slotSize, slotSize);

        // Check if mouse click is within item bounds
        if (itemBounds.contains(static_cast<sf::Vector2f>(mousePosWindow))) {

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mousePressed) {
                mousePressed = true;
                handlePurchase(pair.first, this->player);

				std::cout << pair.first << std::endl;
			
            }
           
        }

        currentSlot++;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        mousePressed = false;
    }
}



void Shop::update(const sf::Vector2i& mousePosWindow)
{
    for (auto& i : this->buttons)
    {
        i.second->update(mousePosWindow);
    }


    this->updateItemSelection(mousePosWindow, player);
}



void Shop::renderButtons(sf::RenderTarget& target)
{
    for (auto& i : this->buttons)
    {
        i.second->render(target);
    }

    this->updateInventoryText();

}

void Shop::renderInventoryText(sf::RenderTarget& target)
{
    target.draw(this->inventoryTextmoney);
}



void Shop::render(sf::RenderTarget& target, const sf::Vector2f& position)
{

    target.draw(this->LisaShop);


  // Define slot size and padding
    float slotSize = 85.0f; // Example size
    float padding = 5.0f;

    int cols = 4; // Number of columns
    int row = 5;
    int currentSlot = 0;

    for (const auto& pair : items) {
        const Item* item = pair.second;
        int row = currentSlot / cols;
        int col = currentSlot % cols;

        float x = position.x + col * (slotSize + padding);
        float y = position.y + row * (slotSize - 10.f);

        sf::Sprite itemSprite = item->getSprite();
        itemSprite.setPosition(x, y + 5.f);

        // Draw item
        target.draw(itemSprite);

        // Render the item quantity (bottom-right corner)
        if (item->getQuantity() > 0) {
            sf::Text quantityText;
            quantityText.setFont(font);
            quantityText.setString(std::to_string(item->getQuantity()));  // Convert quantity to string
            quantityText.setCharacterSize(24);  // Size of the quantity text
            quantityText.setFillColor(sf::Color::Black);  // Text color
            quantityText.setPosition(x + slotSize - 25.f, y + 40.f);
            // Draw the quantity text
            target.draw(quantityText);
        }


        currentSlot++;
    }

    this->renderInventoryText(target);
}
