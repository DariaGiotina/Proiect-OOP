#ifndef INVENTORY_H
#define INVENTORY_H


class Item {
protected:
    std::string id;
    std::string name;
    int quantity;
    bool isStackable;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Item(std::string id, std::string name, int quantity, bool isStackable, const std::string& texturePath)
        : id(id), name(name), quantity(quantity), isStackable(isStackable) {
        if (!texture.loadFromFile(texturePath)) {
            throw std::runtime_error("Failed to load texture for item: " + name);
        }
        sprite.setTexture(texture);
        sprite.setScale(3.5f, 3.5f);
    }

    virtual ~Item() {}

    const std::string& getId() const { return id; }
    const std::string& getName() const { return name; }
    int getQuantity() const { return quantity; }
	bool getIsStackable() const { return isStackable; }
    void setQuantity(int qty) { quantity = qty; }
    const sf::Sprite& getSprite() const { return sprite; }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }

    virtual Item* clone() const {
        return new Item(*this);
    }
};

class Inventory
{
private:
	std::map<std::string, Item*> items;
    sf::Font font;

	void initFont();
public:
	Inventory();
	virtual ~Inventory();

	// Functions
	void addItem(Item* item);
	void removeItem(std::string& id, int quantity);
	int getItemQuantity(const std::string& itemId) const;

    const std::map<std::string, Item*>& getItems() const;


	void render(sf::RenderTarget& target, const sf::Texture& inventoryTexture, const sf::Vector2f& position);
};

#endif // !INVENTORY_H