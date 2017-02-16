#ifndef ITEM_ENTITY_H
#define ITEM_ENTITY_H

#include <string>
#include "Consumables.h"

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
	void Use();
	Consumables* comsumables;

private:
	std::string Name;
	unsigned int Amount;
};

#endif