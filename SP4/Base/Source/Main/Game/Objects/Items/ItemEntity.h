#ifndef ITEM_ENTITY_H
#define ITEM_ENTITY_H

#include <string>
#include "Consumables.h"
#include "Resource.h"
#include "../Characters/CharacterEntity.h"

class ItemEntity
{
public:
	ItemEntity();
	~ItemEntity();

	void SetName(const std::string&);
	void SetAmount(const unsigned int&);

	unsigned int GetAmount();
	std::string GetName();
	void AddAmount(int&);
	void Use(std::string Class, CharacterEntity* Character);
	void Combine(std::string one, std::string two, std::string three, std::string four, std::string five);
	Consumables* comsumables;


private:
	std::string Name;
	unsigned int Amount;
};

#endif