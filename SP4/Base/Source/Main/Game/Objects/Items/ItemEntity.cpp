#include "ItemEntity.h"

ItemEntity::ItemEntity()
{
}

ItemEntity::~ItemEntity()
{
}

void ItemEntity::Use(std::string Item, CharacterEntity* Character)
{
	if (Item == "Red Potion")
	{
		Character->SetHealth(consumables->UseHealthPot(Character->GetHealth()));
	}
	else if (Item == "Blue Potion")
	{
		Character->SetAbilityPoints(consumables->UseManaPot(Character->GetAbilityPoints()));
	}
	else if (Item == "Attack Potion")
	{
		Character->SetAttack(consumables->UseAtkBuffPot(Character->GetAttack()));
	}
	else if (Item == "Defense Potion")
	{
		Character->SetDefense(consumables->UseDefBuffPot(Character->GetDefense()));
	}
	else if (Item == "Bandage")
	{

	}
}

