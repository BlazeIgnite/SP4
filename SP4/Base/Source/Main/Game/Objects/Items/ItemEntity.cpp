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

void ItemEntity::Use(std::string Item, CharacterEntity* Character)
{
	
	if (Name == Item)
	{
		if (GetAmount() > 0)
		{
			Character->SetHealth(comsumables->UseHealthPot(Character->GetHealth()));
			Amount--;
		}
	}
}

//void ItemEntity::Combine(std::string one, std::string two, std::string three, std::string four, std::string five)
//{
//	if (one == "Red Herb" && two == "Reb Herb" && three == "Empty Bottle" && four == "" && five == "")
//	{
//		
//	}
//}
