#ifndef INVENTORY_H
#define INVENTORY_H


class Item{
protected:
	std::string id;
	std::string name;
	int quantity;
	bool isStackable;

public:
	Item(std::string id, std::string name, int quantity, bool isStackable)
		: id(id), name(name), quantity(quantity), isStackable(isStackable) {}

	// Destructor
	virtual ~Item() {}


	const bool& getIsStackable() const 
	{ 
		return isStackable;
	}

	// Getters and setters for other properties
	const std::string& getId() const
	{ 
		return id; 
	}

	const std::string& getName() const 
	{ 
		return name;
	}

	int getQuantity() const
	{ 
		return quantity;
	}

	void setQuantity(int qty) 
	{ 
		quantity = qty; 
	}

	virtual Item* clone() const 
	{
		return new Item(*this); // Use copy constructor
	}

};

class Inventory
{
private:
	std::map<std::string, Item*> items;

public:
	Inventory();
	virtual ~Inventory();

	// Functions
	void addItem(Item* item);
	void removeItem(std::string& id, int quantity);

	const std::map<std::string, Item*>& getItems() const {
		return items;
	}
};

#endif // !INVENTORY_H