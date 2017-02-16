#include "ItemEntity.h"

ItemEntity::ItemEntity()
{
}

ItemEntity::~ItemEntity()
{
}


void ItemEntity::SetName(const std::string& newName)
{
	this->Name = newName;
}

void ItemEntity::SetAmount(const unsigned int& newAmount)
{
	this->Amount = newAmount;
}

std::string ItemEntity::GetName()
{
	return this->Name;
}

unsigned int ItemEntity::GetAmount()
{
	return this->Amount;
}

void ItemEntity::AddAmount(int& AdditionalAmount)
{
	this->Amount += AdditionalAmount;
}

void ItemEntity::Use()
{
	if (Name == "Health")
	{
		//SetHP(comsumables->UseRedPot(GetHP()));
	}
	if (Name == "Mana")
	{
		//SetHP(comsumables->UseManaPot(GetHP()));
	}
}