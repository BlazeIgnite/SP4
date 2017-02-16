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
	void Use(std::string Item, CharacterEntity* Character);
	Consumables* consumables;



private:
	std::string Name;
	unsigned int Amount;
	void UseConsumableItem(std::string, unsigned int);
};

#endif