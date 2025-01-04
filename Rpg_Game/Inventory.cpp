#include "stdafx.h"
#include "Inventory.h"



void Inventory::initFont()
{
    if (!this->font.loadFromFile("Fonts/AncientModernTales-a7Po.ttf"))
    {
        throw("ERROR::INVENTORY::COULD NOT LOAD FONT"); //exits the program and shows the error message
    }
}

Inventory::Inventory()
{
	initFont();

}

Inventory::~Inventory()
{
  /*  for (auto& pair : items) {
        delete pair.second;
    }*/
}

void Inventory::addItem(Item* item)
{
    if (item->getIsStackable() && items.find(item->getId()) != items.end()) {
        items[item->getId()]->setQuantity(items[item->getId()]->getQuantity() + item->getQuantity());
        delete item; // Free memory for the incoming item
    }
    else {
        items[item->getId()] = item; // Store the new item
    }
}

void Inventory::removeItem(std::string& id, int quantity)
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
        std::cout << "Item not found in inventory.\n";
    }
}

int Inventory::getItemQuantity(const std::string& itemId) const
{
    auto it = items.find(itemId);  // Search for the item by its ID
    if (it != items.end()) {
        return it->second->getQuantity();  // Return the quantity if the item is found
    }
    return 0;  // Return 0 if the item is not found
}

const std::map<std::string, Item*>& Inventory::getItems() const
{
	return items;
}


void Inventory::render(sf::RenderTarget& target, const sf::Texture& inventoryTexture, const sf::Vector2f& position) {
    sf::Sprite inventorySprite;
    inventorySprite.setTexture(inventoryTexture);
    inventorySprite.setPosition(position);
	

    // Draw inventory background

    // Define slot size and padding
    float slotSize = 65.0f; // Example size
    float padding = 10.0f;

    int cols = 3; // Number of columns
    int row = 7;
    int currentSlot = 0;

    for (const auto& pair : items) {
        const Item* item = pair.second;
        int row = currentSlot / cols;
        int col = currentSlot % cols;

        float x = position.x + col * (slotSize + padding );
        float y = position.y + row * (slotSize + padding);

        sf::Sprite itemSprite = item->getSprite();
        itemSprite.setPosition(x, y);

        // Draw item
        target.draw(itemSprite);

        // Render the item quantity (bottom-right corner)
        if (item->getQuantity() > 0) {
            sf::Text quantityText;
            quantityText.setFont(font);
            quantityText.setString(std::to_string(item->getQuantity()));  // Convert quantity to string
            quantityText.setCharacterSize(24);  // Size of the quantity text
            quantityText.setFillColor(sf::Color::Black);  // Text color
            quantityText.setPosition(x + slotSize - quantityText.getLocalBounds().width - 5.f, y + slotSize - quantityText.getLocalBounds().height - 5.f);

            float textX = x + slotSize - quantityText.getLocalBounds().width + 0.f;
            float textY = y + slotSize - quantityText.getLocalBounds().height - 5.f;
            quantityText.setPosition(textX, textY);
            // Draw the quantity text
            target.draw(quantityText);
        }

        currentSlot++;
    }
}