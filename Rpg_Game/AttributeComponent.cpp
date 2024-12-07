#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent()
{


	this->exp = 0;
	std::cout << "Exp: " << this->exp << "\n";
	this->level = 1;
	this->expNext = static_cast<unsigned>((50 / 3) * ((pow(this->level + 1, 3) - 6 * pow(this->level + 1, 2)) + (17 * (this->level + 1)) - 12));
	this->attributePoints = 3;

	this->strength = 1;
	this->constitution = 1;
	this->dexterity = 1;
	this->wisdom = 1;
	this->intelligence = 1;
	this->charisma = 1;

	this->hpMax = 4;

	this->updateLevel();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}


//Functions

std::string AttributeComponent::debugPrint() const
{
	std::stringstream ss;

	ss << "Level: " << this->level << "\n"
		<< "Exp: " << this->exp << "\n"
		<< "Exp to next: " << this->expNext << "\n"
		<< "Atribute Points: " << this->attributePoints << "\n";

	return ss.str();
}


void AttributeComponent::gainExp(const unsigned GainedExp)
{
	std::cout << "Gained Exp: " << GainedExp << "\n";
	this->exp += GainedExp; // Add the gained EXP
	this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
	this->hpMax += 2;
	this->damageMax = this->strength * 2 + this->strength / 2;
	this->damageMin = this->strength * 2 + this->strength / 4;
	this->accuracy = this->dexterity * 4 + this->dexterity / 3;
	this->defence = this->constitution * 2 + this->constitution / 4;
	this->luck = this->intelligence * 2 + this->intelligence / 4;


	if (reset) 
	{
		this->hp = this->hpMax;
	}
}

void AttributeComponent::updateLevel()
{
	if (this->exp >= this->expNext)
	{
		this->level++;
		this->exp -= this->expNext;
		this->expNext = static_cast<unsigned>((50 / 3) * ((pow(this->level, 3) - 6 * pow(this->level, 2)) + (17 * this->level) - 12));
		this->attributePoints++;
		std::cout << "Level Up! "<< level << "\n";

		this->updateStats(true);
	}
}

void AttributeComponent::update()
{
	this->updateLevel();
}


