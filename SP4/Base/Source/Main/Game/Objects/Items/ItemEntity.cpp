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
		Character->SetHealth((size_t)consumables->UseHealthPot((int)Character->GetHealth()));
	}
	else if (Item == "Attack Potion")
	{
		Character->SetAttack((size_t)consumables->UseAtkBuffPot((int)Character->GetAttack()));
	}
	else if (Item == "Defence Potion")
	{
		Character->SetDefence((size_t)consumables->UseDefBuffPot((int)Character->GetDefence()));
	}
	else if (Item == "Bandage")
	{

	}
}

