#ifndef INVENTORY_H
#define INVENTORY_H


class Item {

protected:
    std::string id;
    std::string name;
    int quantity;
    bool isStackable;
    sf::Sprite sprite;
    int price;

public:
	static sf::Texture& getTexture(const std::string& path) {
		static std::map<std::string, sf::Texture> textures;
		auto it = textures.find(path);
		if (it == textures.end()) {
			sf::Texture texture;
			if (!texture.loadFromFile(path)) {
				throw std::runtime_error("Failed to load texture: " + path);
			}
			textures[path] = texture;
			return textures[path];
		}
		return it->second;
	}

    Item(std::string id, std::string name, int quantity, bool isStackable, const std::string& texturePath, int price)
        : id(id), name(name), quantity(quantity), isStackable(isStackable), price(price) {
  
        sprite.setTexture(getTexture(texturePath));
        sprite.setScale(3.5f, 3.5f);
    }

    virtual ~Item() {}

    const std::string& getId() const { return id; }
    const std::string& getName() const { return name; }
    int getQuantity() const { return quantity; }
	bool getIsStackable() const { return isStackable; }
    void setQuantity(int qty) { quantity = qty; }
    int getPrice() const { return price; }
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
    static void initItems();
	void addItem(Item* item);
	void removeItem(std::string& id, int quantity);
	int getItemQuantity(const std::string& itemId) const;


    const std::map<std::string, Item*>& getItems() const;

    static Item* getItem(const std::string& id);
   
	void render(sf::RenderTarget& target, const sf::Texture& inventoryTexture, const sf::Vector2f& position);
};

#endif // !INVENTORY_H