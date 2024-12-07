#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H

#include "stdafx.h"

class AttributeComponent
{

public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned attributePoints;

	//Attributes
	int strength;
	int constitution; //agility
	int dexterity;
	int wisdom;
	int intelligence;
	int charisma;

	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int defence;
	int accuracy;
	int luck;

	//Constructor / Destructor
	AttributeComponent();
	virtual ~AttributeComponent();

	//Functions
	std::string debugPrint() const;


	void gainExp(const unsigned exp);

	void updateStats(const bool reset);
	void updateLevel();

	void update();
};

#endif
