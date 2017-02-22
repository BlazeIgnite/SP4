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
	else if (Item == "Attack Potion")
	{
		Character->SetAttack(consumables->UseAtkBuffPot(Character->GetAttack()));
	}
	else if (Item == "Defence Potion")
	{
		Character->SetDefence(consumables->UseDefBuffPot(Character->GetDefence()));
	}
	else if (Item == "Bandage")
	{

	}
}

