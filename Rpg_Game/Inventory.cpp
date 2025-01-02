#include "stdafx.h"
#include "Inventory.h"



Inventory::Inventory()
{
}

Inventory::~Inventory()
{
    for (auto& pair : items) {
        delete pair.second;
    }
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


